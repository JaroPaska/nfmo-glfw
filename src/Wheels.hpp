#ifndef WHEELS_HPP
#define WHEELS_HPP

#include "DynamicModel.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

struct Wheels {
    std::vector<DynamicModel> models;
    std::vector<glm::vec3> pos;
    std::vector<bool> rotates;
    std::vector<float> width;
    std::vector<float> radius;

    Wheels() {}

    Wheels(std::vector<DynamicModel> models, std::vector<glm::vec3> pos, std::vector<bool> rotates,
           std::vector<float> width, std::vector<float> radius)
        : models(models), pos(pos), rotates(rotates), width(width), radius(radius) {}

    static Wheels fromFile(std::string folder) {
        std::string path = folder + "/wheels";
        std::ifstream reader(path);
        if (reader) {
            std::string string;
            std::vector<glm::vec3> pos;
            std::vector<bool> rotates;
            std::vector<float> width;
            std::vector<float> radius;
            while (getline(reader, string)) {
                if (string.rfind("w(", 0) == 0) {
                    pos.push_back(getvec3(string));
                    rotates.push_back(getint(string, 3));
                    width.push_back(getfloat(string, 4));
                    radius.push_back(getfloat(string, 5));
                }
            }
            reader.close();
            std::vector<DynamicModel> models;
            for (int i = 0; i < pos.size(); i++)
                models.push_back(DynamicModel::fromFile(folder + "/wheel" + std::to_string(i)));
            return Wheels(models, pos, rotates, width, radius);
        }
        std::cerr << "Can't open " << path << " (at " << __FILE__ << ":" << __LINE__ << ":"
                  << __func__ << ")" << std::endl;
        return Wheels();
    }
};

#endif