#version 330 core
layout(location = 0) in vec3 in_vertexPos;
layout(location = 1) in vec3 in_polyNormal;
layout(location = 2) in vec3 in_polyColor;

out vec3 fs_polyColor;

uniform vec3 uni_polyColor;
uniform mat4 uni_model;
uniform mat4 uni_view;
uniform mat4 uni_projection;
uniform vec3 uni_snap;
uniform bool uni_light;
uniform bool uni_useUniColor;

void main() {
    gl_Position = uni_projection * uni_view * uni_model * vec4(in_vertexPos, 1.0);

    vec3 polyColor = in_polyColor;
    if (uni_useUniColor)
        polyColor = uni_polyColor;
    if (!uni_light)
        fs_polyColor = polyColor * (vec3(1) + uni_snap);
    else
        fs_polyColor = polyColor;
}