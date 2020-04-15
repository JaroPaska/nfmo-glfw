#version 330 core

in vec3 in_pos;

out vec3 fs_color;

void main() {
    fs_color = vec3(0.5, 0.5, 0);
    gl_Position = vec4(in_pos, 1.0);
}