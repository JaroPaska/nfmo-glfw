#ifndef MODEL_HPP
#define MODEL_HPP

#include "Polygon.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

struct Model {
    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<int> verts;

    Model() {}

    Model(std::vector<unsigned int> VAOs, std::vector<unsigned int> VBOs, std::vector<int> verts)
        : VAOs(VAOs), VBOs(VBOs), verts(verts) {}

    Model(std::vector<glm::vec3> pts, std::vector<Polygon> polys) {
        std::vector<std::vector<Polygon>> polyGroup(POLY_TYPES);
        std::vector<std::vector<Polygon>> linesGroup(LINES_TYPES);
        for (int i = 0; i < polys.size(); i++) {
            polyGroup[polys[i].polyType].push_back(polys[i]);
            if (polys[i].lineType != LINES_NONE)
                linesGroup[polys[i].lineType].push_back(polys[i]);
        }
        VAOs.assign(POLY_TYPES + LINES_TYPES, 0);
        VBOs.assign(POLY_TYPES + LINES_TYPES, 0);
        verts.assign(POLY_TYPES + LINES_TYPES, 0);
        for (int i = 0; i < POLY_TYPES; i++) {
            std::vector<float> buffer;
            for (int j = 0; j < polyGroup[i].size(); j++) {
                for (int k = 0; k < polyGroup[i][j].tris.size(); k++) {
                    for (int l = 0; l < 3; l++) {
                        for (int m = 0; m < 3; m++)
                            buffer.push_back(pts[polyGroup[i][j].tris[k][l]][m]);
                        for (int m = 0; m < 3; m++)
                            buffer.push_back(polyGroup[i][j].normal[m]);
                        for (int m = 0; m < 3; m++)
                            buffer.push_back(polyGroup[i][j].centroid[m]);
                        for (int m = 0; m < 3; m++)
                            buffer.push_back(polyGroup[i][j].color[m] / 255);
                    }
                }
            }
            if (!buffer.empty()) {
                glGenVertexArrays(1, &VAOs[i]);
                glGenBuffers(1, &VBOs[i]);
                glBindVertexArray(VAOs[i]);
                glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
                glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(),
                             GL_STATIC_DRAW);
                for (int j = 0; j < 4; j++) {
                    glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float),
                                          (void *)(3 * j * sizeof(float)));
                    glEnableVertexAttribArray(j);
                }
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
                verts[i] = buffer.size() / 12;
            }
        }
        for (int i = 0; i < LINES_TYPES; i++) {
            std::vector<float> buffer;
            for (int j = 0; j < linesGroup[i].size(); j++) {
                int n = linesGroup[i][j].pts.size();
                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < 2; l++) {
                        for (int m = 0; m < 3; m++)
                            buffer.push_back(pts[linesGroup[i][j].pts[(k + l) % n]][m]);
                    }
                }
            }
            if (!buffer.empty()) {
                glGenVertexArrays(1, &VAOs[POLY_TYPES + i]);
                glGenBuffers(1, &VBOs[POLY_TYPES + i]);
                glBindVertexArray(VAOs[POLY_TYPES + i]);
                glBindBuffer(GL_ARRAY_BUFFER, VBOs[POLY_TYPES + i]);
                glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(),
                             GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
                verts[POLY_TYPES + i] = buffer.size() / 3;
            }
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
};

#endif