#ifndef STAGEOBJECT_H
#define STAGEOBJECT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct StageObject {
    glm::vec3 pos = glm::vec3(0.f);
    glm::quat rot = glm::quat();
    glm::vec3 scale = glm::vec3(1.f);
};
#endif