#ifndef STAGE_H
#define STAGE_H
#include "StagePart.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>

const float GROUND = 250;
const glm::vec3 X_AXIS = glm::vec3(1.f, 0.f, 0.f);
const glm::vec3 Y_AXIS = glm::vec3(0.f, -1.f, 0.f);
const glm::vec3 Z_AXIS = glm::vec3(0.f, 0.f, 1.f);

struct Stage {
    glm::vec3 snap = glm::vec3();
    glm::vec3 sky = glm::vec3(170.f, 220.f, 255.f);
    glm::vec3 grnd = glm::vec3(205.f, 200.f, 200.f);
    glm::vec3 fog = glm::vec3(255.f, 220.f, 220.f);
    float fadefrom;
    int nlaps;
    int nfix;
    bool scenery;
    std::vector<std::shared_ptr<StagePart>> stageParts;
    std::vector<std::shared_ptr<StagePart>> checkPoints;
    std::vector<std::shared_ptr<StagePart>> fixPoints;
    Stage();
    Stage(std::string path);
};
#endif