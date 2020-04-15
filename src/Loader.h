#ifndef LOADER_H
#define LOADER_H
#include "Model.h"
#include <memory>
#include <unordered_set>

struct Loader {
    static void loadModel(std::shared_ptr<Model> model);
};
#endif