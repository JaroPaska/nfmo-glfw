#ifndef STAGE_H
#define STAGE_H
#include "Model.h"
#include "StageObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

const float GROUND = 250;
const float skyline = -300;

struct Stage {
    int nextID = 0;
    std::unique_ptr<Model> groundModel;
    std::unique_ptr<Model> polys1Model;
    std::unique_ptr<Model> polys2Model;
    std::unique_ptr<Model> cloudsModel;
    std::unique_ptr<Model> mountainsModel;
    glm::vec3 snap = glm::vec3();
    glm::vec3 sky = glm::vec3(170, 220, 255);
    glm::vec3 grnd = glm::vec3(205, 200, 200);
    glm::vec3 fog = glm::vec3(255, 220, 220);
    glm::vec3 lightDirection = -Y_AXIS;
    float fadefrom = 7500;
    bool lightson = false;
    int nlaps = 0;
    int nfix = 1;
    bool scenery = true;
    std::unordered_map<int, std::unique_ptr<StageObject>> stageObjects;
    std::vector<int> checkPoints;
    std::vector<int> fixPoints;
    Stage();
    Stage(std::string path);
};
#endif