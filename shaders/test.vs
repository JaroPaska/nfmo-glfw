#version 330 core

in vec3 in_vertexPos;
in vec3 in_color;
uniform mat4 uni_model;
uniform mat4 uni_view;
uniform mat4 uni_projection;
out vec3 fs_color;

void main() {
    fs_color = in_color;
    gl_Position = uni_projection * uni_view * uni_model * vec4(in_vertexPos, 1.0);
}