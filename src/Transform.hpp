#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Transform {
    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale = glm::vec3(1);

    Transform() {}

    Transform(float x, float y, float z) : pos(glm::vec3(x, y, z)) {}

    Transform(float x, float y, float z, float xz) : Transform(x, y, z) {
        rot = glm::rotate(glm::quat(), glm::radians(xz), Y_AXIS);
    }
};

const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
const glm::vec3 Y_AXIS = glm::vec3(0, -1, 0);
const glm::vec3 Z_AXIS = glm::vec3(0, 0, 1);

#endif