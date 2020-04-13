#version 330 core
in vec3 fs_polyColor;

out vec3 out_polyColor;

void main() {
    out_polyColor = vec4(fs_polyColor, 1.f);
}