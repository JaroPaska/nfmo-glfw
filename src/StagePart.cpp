#include "Stage.h"
#include "StagePart.h"

StagePart::StagePart(int type, float x, float y, float z, float xz) {
    this->type = type;
    this->pos = glm::vec3(x, y, z);
    this->rot = glm::rotate(glm::quat(), glm::radians(xz), Y_AXIS);
    this->scale = glm::vec3(1.f);
}

bool StagePart::isScenery(int type) { return type >= 65 && type <= 75; }

bool StagePart::isCheckpoint(int type) { return type == CHECKPOINT || type == OFFROAD_CHECKPOINT; }

bool StagePart::isFixpoint(int type) { return type == FIXING_HOOP; }