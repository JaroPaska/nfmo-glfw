#version 330 core
in vec3 fs_polyColor;
in vec4 fs_fragViewPos;

out vec4 out_polyColor;

uniform bool uni_doFog;
uniform vec3 uni_fog;
uniform float uni_fadefrom;
uniform float uni_density;

void main() {
    float visibility = 1.0;
    if (uni_doFog) {
        visibility = pow(uni_density, (length(fs_fragViewPos.xyz) - uni_fadefrom) / uni_fadefrom);
        visibility = clamp(visibility, 0.0, 1.0);
    }
    out_polyColor = vec4(mix(uni_fog, fs_polyColor, visibility), 1);
}