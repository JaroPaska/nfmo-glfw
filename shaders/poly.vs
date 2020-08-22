#version 330 core
layout(location = 0) in vec3 in_vertexPos;
layout(location = 1) in vec3 in_polyNormal;
layout(location = 2) in vec3 in_polyCentroid;
layout(location = 3) in vec3 in_polyColor;

out vec3 fs_modelPos;
out vec3 fs_viewPos;
out vec4 fs_lightSpacePos[4];
out vec3 fs_polyColor;
out float fs_diff;

uniform mat4 uni_model;
uniform mat4 uni_invModel;
uniform mat4 uni_view;
uniform mat4 uni_invView;
uniform mat4 uni_projection;
uniform bool uni_doSnap;
uniform vec3 uni_snap;
uniform bool uni_light;
uniform bool uni_useUniColor;
uniform vec3 uni_polyColor;

uniform vec3 uni_lightDirection;
uniform mat4 lightViewProjection[4];

void main() {
    vec4 modelPos = uni_model * vec4(in_vertexPos, 1.0);
    vec4 viewPos = uni_view * modelPos;
    gl_Position = uni_projection * viewPos;
    fs_viewPos = viewPos.xyz;

    vec3 polyColor = in_polyColor;
    if (uni_useUniColor)
        polyColor = uni_polyColor;
    if (!uni_light) {
        vec3 cameraPos = vec3(uni_invView[3][0], uni_invView[3][1], uni_invView[3][2]);
        vec3 C = vec3(uni_model * vec4(in_polyCentroid, 1.0));
        vec3 N = normalize(mat3(transpose(uni_invModel)) * in_polyNormal);
        float diff = 0;
        if (sign(dot(N, uni_lightDirection)) == sign(dot(N, C - cameraPos)))
            diff = abs(dot(N, uni_lightDirection));
        fs_polyColor = (0.5 + 0.5 * diff) * polyColor;
    } else
        fs_polyColor = polyColor;
    if (uni_doSnap)
        fs_polyColor *= (vec3(1) + uni_snap);
}