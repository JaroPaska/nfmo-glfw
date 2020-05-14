#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <memory>

struct RawModel {
    unsigned int VAO;
    unsigned int VBO;
    int vertices;
    RawModel();
    ~RawModel();
    static const std::shared_ptr<RawModel> &ground(float size, int parts);
};
#endif