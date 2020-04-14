#ifndef MODEL_H
#define MODEL_H
#include "Polygon.h"
#include <memory>
#include <string>

struct Model {
    std::vector<glm::vec3> points;
    std::vector<std::shared_ptr<Polygon>> polygons;
    Model(std::string path);
    Model(std::string path, glm::vec3 firstColor, glm::vec3 secondColor);
};
#endif