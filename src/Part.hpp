#ifndef PART_HPP
#define PART_HPP

#include "DynamicModel.hpp"
#include "StaticModel.hpp"
#include "Transform.hpp"
#include <string>

struct Part {
    StaticModel *model = nullptr;
    Transform transform = Transform();

    Part() {}

    Part(StaticModel *model, Transform transform = Transform())
        : model(model), transform(transform) {}

    static Part *FromFile(std::string folder) {
        StaticModel *model = DynamicModel::FromFile(folder);
        return new Part(model);
    }

    static Part *FromPart(Part *part, Transform transform = Transform()) {
        return new Part(part->model, transform)
    }

    virtual ~Part() { delete model; }
};

#endif