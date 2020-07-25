#include "StageObject.h"

StageObject::StageObject() {
    this->type = -1;
    this->pos = glm::vec3(0);
    this->rot = glm::quat();
    this->scale = glm::vec3(1);
}

StageObject::StageObject(int type, float x, float y, float z, float xz) {
    this->type = type;
    this->pos = glm::vec3(x, y, z);
    this->rot = glm::rotate(glm::quat(), glm::radians(xz), Y_AXIS);
    this->scale = glm::vec3(1);
}

bool StageObject::isScenery(int type) { return type >= 65 && type <= 75; }

bool StageObject::isCheckpoint(int type) {
    return type == CHECKPOINT || type == OFFROAD_CHECKPOINT || type == ROLLERCOASTER_CHECKPOINT;
}

bool StageObject::isFixpoint(int type) { return type == FIXING_HOOP; }