#include "Get.h"
#include "Model.h"
#include <fstream>

Model::Model(std::string path) {
    std::string string;
    std::ifstream reader(path + "/modelInfo.txt");
    while (getline(reader, string)) {
        if (string.rfind("v(", 0) == 0)
            points.push_back(getvec3(string));
        if (string.rfind("<p>", 0) == 0)
            polygons.push_back(std::shared_ptr<Polygon>(new Polygon()));
        if (!polygons.empty()) {
            if (string.rfind("c(", 0) == 0)
                polygons.back()->color = getvec3(string);
            if (string.rfind("colnum(", 0) == 0)
                polygons.back()->colnum = getint(string, 0);
            if (string.rfind("glass(", 0) == 0)
                polygons.back()->material = MATERIAL_GLASS;
            if (string.rfind("light(", 0) == 0)
                polygons.back()->material = MATERIAL_LIGHT;
            if (string.rfind("outline(", 0) == 0)
                polygons.back()->lines = LINES_FLAT_COLOR;
            if (string.rfind("charged(", 0) == 0)
                polygons.back()->lines = LINES_CHARGED;
            if (string.rfind("p(", 0) == 0) {
                int npoints = getint(string, 0);
                for (int i = 0; i < npoints; i++)
                    polygons.back()->pointIndices.push_back(getint(string, i + 1));
            }
            if (string.rfind("t(", 0) == 0) {
                polygons.back()->triangles.push_back({});
                for (int i = 0; i < 3; i++)
                    polygons.back()->triangles.back().push_back(getint(string, i));
            }
        }
    }
}