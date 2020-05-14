#ifndef LOADER_H
#define LOADER_H
#include "Model.h"
#include <unordered_set>

struct Loader {
    static void loadModels();
    static void loadShaders();
};
#endif