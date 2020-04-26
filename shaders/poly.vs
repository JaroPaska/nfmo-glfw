#version 330 core
layout(location = 0) in vec3 in_vertexPos;
layout(location = 1) in vec3 in_polyNormal;
layout(location = 2) in vec3 in_polyCentroid;
layout(location = 3) in vec3 in_polyColor;

out vec3 fs_polyColor;

uniform mat4 uni_model;
uniform mat4 uni_invModel;
uniform mat4 uni_view;
uniform mat4 uni_invView;
uniform mat4 uni_projection;
uniform vec3 uni_snap;
uniform vec3 uni_lightDirection;
uniform bool uni_light;
uniform bool uni_useUniColor;
uniform vec3 uni_polyColor;

void main() {
    gl_Position = uni_projection * uni_view * uni_model * vec4(in_vertexPos, 1.0);

    vec3 polyColor = in_polyColor;
    if (uni_useUniColor)
        polyColor = uni_polyColor;
    if (!uni_light) {
        vec3 cameraPos = vec3(uni_invView[3][0], uni_invView[3][1], uni_invView[3][2]);
        vec3 C = vec3(uni_model * vec4(in_polyCentroid, 1.0));
        vec3 N = normalize(mat3(transpose(uni_invModel)) * in_polyNormal);
        float diff = 0;
        if (sign(dot(N, uni_lightDirection)) == sign(dot(N, C - cameraPos)))
            diff = dot(N, uni_lightDirection);
        if (diff < 0)
            diff = -diff;
        fs_polyColor = (0.5 + 0.5 * diff) * polyColor * (vec3(1) + uni_snap);
    } else
        fs_polyColor = polyColor;
}