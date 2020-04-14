#ifndef POLYGON_H
#define POLYGON_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

const int MATERIAL_FLAT_COLOR = 0;
const int MATERIAL_GLASS = 1;
const int MATERIAL_LIGHT = 2;
const int LINES_NONE = 0;
const int LINES_FLAT_COLOR = 1;
const int LINES_CHARGED = 2;

struct Polygon {
    std::vector<int> pointIndices;
    std::vector<std::vector<int>> triangles;
    glm::vec3 normal = glm::vec3();
    glm::vec3 color = glm::vec3();
    glm::vec3 lightColor = glm::vec3();
    glm::vec3 lineColor = glm::vec3();
    int material = MATERIAL_FLAT_COLOR;
    int lines = LINES_NONE;
    int colnum = 0;
};
#endif