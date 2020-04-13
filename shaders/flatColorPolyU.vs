#version 330 core
in vec3 in_vertexPos;
in vec3 in_polyNormal;

out vec3 fs_polyColor;

uniform vec3 uni_polyColor;
uniform mat4 uni_mvpMatrix;
uniform vec3 uni_snap;

void main() {
    gl_Position = in_vertexPos * uni_mvpMatrix;
    fs_polyColor = uni_polyColor * (vec3(1) + uni_snap);
}