#version 330 core
in vec3 in_vertexPos;
in vec3 in_polyNormal;
in vec3 in_polyColor;

out vec3 fs_polyColor;

uniform vec3 uni_polyColor;
uniform mat4 uni_mvpMatrix;
uniform vec3 uni_snap;
uniform bool uni_light;
uniform bool uni_useUniColor;

void main() {
    gl_Position = in_vertexPos * uni_mvpMatrix;

    vec3 polyColor = in_polyColor;
    if (uni_useUniColor)
        polyColor = uni_polyColor;
    if (!uni_light)
        fs_polyColor = polyColor * (vec3(1) + uni_snap);
    else
        fs_polyColor = polyColor;
}