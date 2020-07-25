#version 330 core
in vec3 fs_modelPos;
in vec3 fs_viewPos;
in vec4 fs_lightSpacePos[4];
in vec3 fs_polyColor;
in float fs_diff;

out vec4 out_polyColor;

uniform bool uni_doFog;
uniform vec3 uni_fog;
uniform float uni_fadefrom;
uniform float uni_density;
uniform sampler2D uni_depthMap[4];

bool contains(int i) {
    vec3 projCoords = fs_lightSpacePos[i].xyz / fs_lightSpacePos[i].w;
    projCoords = projCoords * 0.5 + 0.5;
    if (projCoords.x >= 0 && projCoords.x < 1 && projCoords.y >= 0 && projCoords.y < 1)
        return true;
    else
        return false;
}

bool shadowed() {
    int i = 0;
    while (i < 4 && !contains(i))
        ++i;
    if (i == 4)
        return false;
    vec3 projCoords = fs_lightSpacePos[i].xyz / fs_lightSpacePos[i].w;
    projCoords = projCoords * 0.5 + 0.5;
    if (projCoords.z < 0.0 || projCoords.z > 1.0)
        return false;
    float closestDepth = texture(uni_depthMap[0], projCoords.xy).r;
    float bias = max(0.002 * (1.0 - fs_diff), 0.001);
    return projCoords.z - bias > closestDepth ? true : false;
}

void main() {
    float visibility = 1.0;
    if (uni_doFog) {
        visibility = pow(uni_density, (length(fs_viewPos) - uni_fadefrom) / uni_fadefrom);
        visibility = clamp(visibility, 0.0, 1.0);
    }
    out_polyColor = vec4(mix(uni_fog, fs_polyColor, visibility), 1);
}