#ifndef STAGE_H
#define STAGE_H
#include "StagePart.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

struct Stage {
    glm::vec3 snap;
    glm::vec3 osky;
    glm::vec3 sky;
    glm::vec3 ogrnd;
    glm::vec3 grnd;
    glm::vec3 ofog;
    glm::vec3 fog;
    float fadefrom;
    int nlaps;
    int nfix;
    bool scenery;
    std::vector<StagePart*> stageparts;
    std::vector<StagePart*> checkpoints;
    std::vector<StagePart*> fixpoints;
    Stage();
    Stage(int stage);
    ~Stage();
};

const float GROUND = 250;
const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
const glm::vec3 Y_AXIS = glm::vec3(0, -1, 0);
const glm::vec3 Z_AXIS = glm::vec3(0, 0, 1);
#endif