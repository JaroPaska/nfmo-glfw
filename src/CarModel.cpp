#include "CarModel.h"

CarModel::CarModel(std::string path) : Model(path) {
    for (int i = 0; i < 4; i++)
        wheelModels[i] = std::shared_ptr<Model>(new Model(path + "/wheel"));
}