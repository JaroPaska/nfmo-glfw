#include "Get.h"
#include "Model.h"
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>

bool ccw(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    glm::vec3 axis_x = glm::normalize(b - a);
    glm::vec3 axis_y = glm::normalize(c - a);
    glm::vec3 axis_z = glm::cross(axis_x, axis_y);

    glm::mat3x3 object_transform;
    object_transform[0] = axis_x;
    object_transform[1] = axis_y;
    object_transform[2] = axis_z;

    glm::mat3x3 object_to_world_transform = glm::inverse(object_transform);
    glm::vec3 normal = object_to_world_transform * axis_z;

    return normal.z > 0;
}

Model::Model(std::string path) {
    std::string string;
    std::ifstream reader(path + "/modelInfo");
    while (getline(reader, string)) {
        if (string.rfind("v(", 0) == 0)
            points.push_back(getvec3(string));
        if (string.rfind("<p>", 0) == 0)
            polygons.push_back(std::shared_ptr<Polygon>(new Polygon()));
        if (!polygons.empty()) {
            if (string.rfind("n(", 0) == 0)
                polygons.back()->normal = getvec3(string);
            if (string.rfind("C(", 0) == 0)
                polygons.back()->centroid = getvec3(string);
            if (string.rfind("c(", 0) == 0)
                polygons.back()->color = getvec3(string);
            if (string.rfind("colnum(", 0) == 0)
                polygons.back()->colnum = getint(string, 0);
            if (string.rfind("glass(", 0) == 0)
                polygons.back()->polyType = POLYS_GLASS;
            if (string.rfind("light(", 0) == 0)
                polygons.back()->polyType = POLYS_LIGHT;
            if (string.rfind("outline(", 0) == 0)
                polygons.back()->lineType = LINES_FLAT_COLOR;
            if (string.rfind("charged(", 0) == 0)
                polygons.back()->lineType = LINES_CHARGED;
            if (string.rfind("p(", 0) == 0) {
                int npoints = getint(string, 0);
                for (int i = 0; i < npoints; i++)
                    polygons.back()->pointIndices.push_back(getint(string, i + 1));
            }
            if (string.rfind("t(", 0) == 0) {
                polygons.back()->triangles.push_back({});
                for (int i = 0; i < 3; i++)
                    polygons.back()->triangles.back().push_back(getint(string, i));
            }
        }
    }
    reader.close();
}

Model::~Model() {
    for (int i = 0; i < polyVAOs.size(); i++)
        glDeleteVertexArrays(1, &polyVAOs[i]);
    for (int i = 0; i < polyVBOs.size(); i++)
        glDeleteBuffers(1, &polyVBOs[i]);
}