#include "Get.h"
#include "Loader.h"
#include "Model.h"
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <memory>

Model::Model() {}

Model::Model(std::string path) {
    std::string string;
    std::ifstream reader(path + "/modelInfo");
    while (getline(reader, string)) {
        if (string.rfind("v(", 0) == 0)
            points.push_back(getvec3(string));
        if (string.rfind("<p>", 0) == 0)
            polygons.push_back(std::make_shared<Polygon>());
        if (!polygons.empty()) {
            if (string.rfind("n(", 0) == 0)
                polygons.back()->normal = getvec3(string);
            if (string.rfind("C(", 0) == 0)
                polygons.back()->centroid = getvec3(string);
            if (string.rfind("c(", 0) == 0)
                polygons.back()->color = getvec3(string);
            if (string.rfind("colnum(", 0) == 0)
                polygons.back()->colnum = getint(string, 0);
            if (string.rfind("glass(", 0) == 0)
                polygons.back()->polyType = POLYS_GLASS;
            if (string.rfind("light(", 0) == 0)
                polygons.back()->polyType = POLYS_LIGHT;
            if (string.rfind("finish(", 0) == 0)
                polygons.back()->polyType = POLYS_FINISH;
            if (string.rfind("outline(", 0) == 0)
                polygons.back()->lineType = LINES_FLAT_COLOR;
            if (string.rfind("charged(", 0) == 0)
                polygons.back()->lineType = LINES_CHARGED;
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
    reader.close();

    std::vector<std::vector<std::shared_ptr<Polygon>>> byPolyType(POLYS_TYPES);
    std::vector<std::vector<std::shared_ptr<Polygon>>> byLineType(LINES_TYPES);
    for (int i = 0; i < polygons.size(); i++) {
        byPolyType[polygons[i]->polyType].push_back(polygons[i]);
        if (polygons[i]->lineType != LINES_NONE)
            byLineType[polygons[i]->lineType].push_back(polygons[i]);
    }

    polyVAOs.assign(POLYS_TYPES, 0);
    polyVBOs.assign(POLYS_TYPES, 0);
    polyVertexCount.assign(POLYS_TYPES, 0);
    for (int i = 0; i < POLYS_TYPES; i++) {
        std::vector<float> buffer;
        for (int j = 0; j < byPolyType[i].size(); j++) {
            for (int k = 0; k < byPolyType[i][j]->triangles.size(); k++) {
                for (int l = 0; l < 3; l++) {
                    for (int m = 0; m < 3; m++)
                        buffer.push_back(points[byPolyType[i][j]->triangles[k][l]][m]);
                    for (int m = 0; m < 3; m++)
                        buffer.push_back(byPolyType[i][j]->normal[m]);
                    for (int m = 0; m < 3; m++)
                        buffer.push_back(byPolyType[i][j]->centroid[m]);
                    for (int m = 0; m < 3; m++)
                        buffer.push_back(byPolyType[i][j]->color[m] / 255.f);
                }
            }
        }
        if (!buffer.empty()) {
            glGenVertexArrays(1, &polyVAOs[i]);
            glGenBuffers(1, &polyVBOs[i]);
            glBindVertexArray(polyVAOs[i]);
            glBindBuffer(GL_ARRAY_BUFFER, polyVBOs[i]);
            glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(),
                         GL_STATIC_DRAW);
            for (int j = 0; j < 4; j++) {
                glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float),
                                      (void *)(3 * j * sizeof(float)));
                glEnableVertexAttribArray(j);
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            polyVertexCount[i] = buffer.size() / 12;
        }
    }
    lineVAOs.assign(LINES_TYPES, 0);
    lineVBOs.assign(LINES_TYPES, 0);
    lineVertexCount.assign(LINES_TYPES, 0);
    for (int i = 0; i < LINES_TYPES; i++) {
        std::vector<float> buffer;
        for (int j = 0; j < byLineType[i].size(); j++) {
            int n = byLineType[i][j]->pointIndices.size();
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < 2; l++) {
                    for (int m = 0; m < 3; m++)
                        buffer.push_back(points[byLineType[i][j]->pointIndices[(k + l) % n]][m]);
                }
            }
        }
        if (!buffer.empty()) {
            glGenVertexArrays(1, &lineVAOs[i]);
            glGenBuffers(1, &lineVBOs[i]);
            glBindVertexArray(lineVAOs[i]);
            glBindBuffer(GL_ARRAY_BUFFER, lineVBOs[i]);
            glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(),
                         GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            lineVertexCount[i] = buffer.size() / 3;
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Model::~Model() {
    for (int i = 0; i < polyVAOs.size(); i++)
        glDeleteVertexArrays(1, &polyVAOs[i]);
    for (int i = 0; i < polyVBOs.size(); i++)
        glDeleteBuffers(1, &polyVBOs[i]);
}