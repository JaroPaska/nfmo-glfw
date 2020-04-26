#ifndef POLYGON_H
#define POLYGON_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

const int POLYS_FLAT_COLOR = 0;
const int POLYS_GLASS = 1;
const int POLYS_LIGHT = 2;
const int POLYS_TYPES = 3;
const int LINES_NONE = -1;
const int LINES_FLAT_COLOR = 0;
const int LINES_CHARGED = 1;
const int LINES_TYPES = 2;

struct Polygon {
    std::vector<int> pointIndices;
    std::vector<std::vector<int>> triangles;
    glm::vec3 normal = glm::vec3();
    glm::vec3 centroid = glm::vec3();
    glm::vec3 color = glm::vec3();
    int polyType = POLYS_FLAT_COLOR;
    int lineType = LINES_NONE;
    int colnum = 0;
};
#endif