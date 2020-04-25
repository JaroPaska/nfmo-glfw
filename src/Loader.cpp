#include "Loader.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>

void Loader::loadModel(std::shared_ptr<Model> model) {
    std::vector<std::vector<std::shared_ptr<Polygon>>> byPolyType(POLYS_TYPES);
    std::vector<std::vector<std::shared_ptr<Polygon>>> byLineType(LINES_TYPES);
    for (int i = 0; i < model->polygons.size(); i++) {
        byPolyType[model->polygons[i]->polyType].push_back(model->polygons[i]);
        if (model->polygons[i]->lineType != LINES_NONE)
            byLineType[model->polygons[i]->lineType].push_back(model->polygons[i]);
    }

    model->polyVAOs.assign(POLYS_TYPES, 0);
    model->polyVBOs.assign(POLYS_TYPES, 0);
    model->polyVertexCount.assign(POLYS_TYPES, 0);
    for (int i = 0; i < POLYS_TYPES; i++) {
        std::vector<float> buffer;
        for (int j = 0; j < byPolyType[i].size(); j++) {
            for (int k = 0; k < byPolyType[i][j]->triangles.size(); k++) {
                for (int l = 0; l < 3; l++) {
                    for (int m = 0; m < 3; m++)
                        buffer.push_back(model->points[byPolyType[i][j]->triangles[k][l]][m]);
                    for (int m = 0; m < 3; m++)
                        buffer.push_back(byPolyType[i][j]->normal[m]);
                    for (int m = 0; m < 3; m++)
                        buffer.push_back(byPolyType[i][j]->color[m] / 255.f);
                }
            }
        }
        if (!buffer.empty()) {
            glGenVertexArrays(1, &model->polyVAOs[i]);
            glGenBuffers(1, &model->polyVBOs[i]);
            glBindVertexArray(model->polyVAOs[i]);
            glBindBuffer(GL_ARRAY_BUFFER, model->polyVBOs[i]);
            glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(),
                         GL_STATIC_DRAW);
            for (int j = 0; j < 3; j++) {
                glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
                                      (void *)(3 * j * sizeof(float)));
                glEnableVertexAttribArray(j);
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            model->polyVertexCount[i] = buffer.size() / 9;
        }
    }
    model->lineVAOs.assign(LINES_TYPES, 0);
    model->lineVBOs.assign(LINES_TYPES, 0);
    model->lineVertexCount.assign(LINES_TYPES, 0);
    for (int i = 0; i < LINES_TYPES; i++) {
        std::vector<float> buffer;
        for (int j = 0; j < byLineType[i].size(); j++) {
            int n = byLineType[i][j]->pointIndices.size();
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < 2; l++) {
                    for (int m = 0; m < 3; m++)
                        buffer.push_back(
                            model->points[byLineType[i][j]->pointIndices[(k + l) % n]][m]);
                }
            }
        }
        if (!buffer.empty()) {
            glGenVertexArrays(1, &model->lineVAOs[i]);
            glGenBuffers(1, &model->lineVBOs[i]);
            glBindVertexArray(model->lineVAOs[i]);
            glBindBuffer(GL_ARRAY_BUFFER, model->lineVBOs[i]);
            glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(),
                         GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            model->lineVertexCount[i] = buffer.size() / 3;
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Loader::loadModels() {
    std::vector<std::string> modelDirs{
        "road",          "froad",    "twister2",      "twister1", "turn",      "offroad",
        "bumproad",      "offturn",  "nroad",         "nturn",    "roblend",   "noblend",
        "rnblend",       "roadend",  "offroadend",    "hpground", "ramp30",    "cramp35",
        "dramp15",       "dhilo15",  "slide10",       "takeoff",  "sramp22",   "offbump",
        "offramp",       "sofframp", "halfpipe",      "spikes",   "rail",      "thewall",
        "checkpoint",    "fixpoint", "offcheckpoint", "sideoff",  "bsideoff",  "uprise",
        "riseroad",      "sroad",    "soffroad",      "tside",    "launchpad", "thenet",
        "speedramp",     "offhill",  "slider",        "uphill",   "roll1",     "roll2",
        "roll3",         "roll4",    "roll5",         "roll6",    "opile1",    "opile2",
        "aircheckpoint", "tree1",    "tree2",         "tree3",    "tree4",     "tree5",
        "tree6",         "tree7",    "tree8",         "cac1",     "cac2",      "cac3",
        "8sroad",        "8soffroad"};
    for (int i = 0; i < modelDirs.size(); i++) {
        Renderer::models[i + 10] = std::shared_ptr<Model>(new Model("models/" + modelDirs[i]));
        loadModel(Renderer::models[i + 10]);
    }
}

void Loader::loadShaders() {
    Renderer::polyShader =
        std::shared_ptr<Shader>(new Shader("shaders/poly.vs", "shaders/poly.fs"));
}