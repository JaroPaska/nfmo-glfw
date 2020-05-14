#include "CarModel.h"

CarModel::CarModel(std::string path) : Model(path) {
    for (int i = 0; i < 4; i++)
        wheelModels[i] = std::make_shared<Model>(path + "/wheel");
}