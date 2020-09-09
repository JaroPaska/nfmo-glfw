#ifndef DYNAMICMODEL_HPP
#define DYNAMICMODEL_HPP

#include "Getters.hpp"
#include "StaticModel.hpp"
#include "Polygon.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct DynamicModel : StaticModel {
    std::vector<glm::vec3> pts;
    std::vector<Polygon> polys;

    DynamicModel() {}

    DynamicModel(std::vector<glm::vec3> pts, std::vector<Polygon> polys)
        : StaticModel(pts, polys), pts(pts), polys(polys) {}

    ~DynamicModel() {
        for (int i = 0; i < POLY_TYPES + LINES_TYPES; i++) {
            glDeleteVertexArrays(1, &VAOs[i]);
            glDeleteBuffers(1, &VBOs[i]);
        }
    }

    static DynamicModel *FromFile(std::string folder) {
        std::string path = folder + "/model";
        std::ifstream reader(path);
        if (reader) {
            std::string string;
            std::vector<glm::vec3> pts;
            std::vector<Polygon> polys;
            while (getline(reader, string)) {
                if (string.rfind("v(", 0) == 0)
                    pts.push_back(getvec3(string, 0));
                if (string.rfind("<p>", 0) == 0)
                    polys.push_back(Polygon());
                if (!polys.empty()) {
                    if (string.rfind("n(", 0) == 0)
                        polys.back().normal = getvec3(string, 0);
                    if (string.rfind("C(", 0) == 0)
                        polys.back().centroid = getvec3(string, 0);
                    if (string.rfind("c(", 0) == 0)
                        polys.back().color = getvec3(string, 0);
                    if (string.rfind("colnum(", 0) == 0)
                        polys.back().colnum = getint(string, 0);
                    if (string.rfind("glass(", 0) == 0)
                        polys.back().polyType = POLY_GLASS;
                    if (string.rfind("light(", 0) == 0)
                        polys.back().polyType = POLY_LIGHT;
                    if (string.rfind("finish(", 0) == 0)
                        polys.back().polyType = POLY_FINISH;
                    if (string.rfind("outline(", 0) == 0)
                        polys.back().lineType = LINES_FLAT_COLOR;
                    if (string.rfind("charged(", 0) == 0)
                        polys.back().lineType = LINES_CHARGED;
                    if (string.rfind("p(", 0) == 0) {
                        int npts = getint(string, 0);
                        for (int i = 0; i < npts; i++)
                            polys.back().pts.push_back(getint(string, i + 1));
                    }
                    if (string.rfind("t(", 0) == 0) {
                        polys.back().tris.push_back({});
                        for (int i = 0; i < 3; i++)
                            polys.back().tris.back().push_back(getint(string, i));
                    }
                }
            }
            reader.close();
            return new DynamicModel(pts, polys);
        }
        std::cerr << "Can't open " << path << " (at " << __FILE__ << ":" << __LINE__ << ":"
                  << __func__ << ")" << std::endl;
        return nullptr;
    }
};

#endif