#ifndef MODEL_HPP
#define MODEL_HPP

#include "Polygon.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

struct Model {
    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<int> verts;
    std::vector<glm::vec3> pts;
    std::vector<Polygon> polys;
};

#endif