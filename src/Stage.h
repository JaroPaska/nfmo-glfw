#ifndef STAGE_H
#define STAGE_H
#include "Model.h"
#include "RawModel.h"
#include "StagePart.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>

const float GROUND = 250;
const float skyline = -300;
const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
const glm::vec3 Y_AXIS = glm::vec3(0, -1, 0);
const glm::vec3 Z_AXIS = glm::vec3(0, 0, 1);

struct Stage {
    std::shared_ptr<Model> groundModel;
    std::shared_ptr<Model> polys1Model;
    std::shared_ptr<Model> polys2Model;
    std::shared_ptr<Model> cloudsModel;
    std::shared_ptr<Model> mountainsModel;
    glm::vec3 snap = glm::vec3();
    glm::vec3 sky = glm::vec3(170, 220, 255);
    glm::vec3 grnd = glm::vec3(205, 200, 200);
    glm::vec3 fog = glm::vec3(255, 220, 220);
    glm::vec3 lightDirection = -Y_AXIS;
    float fadefrom = 7500;
    bool lightson = false;
    int nlaps = 0;
    int nfix = 0;
    bool scenery = true;
    std::vector<std::shared_ptr<StagePart>> stageParts;
    std::vector<std::shared_ptr<StagePart>> checkPoints;
    std::vector<std::shared_ptr<StagePart>> fixPoints;
    Stage();
    Stage(std::string path);
};
#endif