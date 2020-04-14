#ifndef CARMODEL_H
#define CARMODEL_H
#include "Model.h"

struct CarModel : Model {
    std::vector<std::shared_ptr<Model>> wheelModels;
};
#endif