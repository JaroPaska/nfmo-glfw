#ifndef RENDERER_H
#define RENDERER_H
#include "Model.h"
#include "Shader.h"
#include "Stage.h"
#include "StageObject.h"
#include "StagePart.h"
#include <memory>
#include <vector>
#include <unordered_map>

struct Renderer {
    static std::shared_ptr<Shader> polyShader;
    static std::unordered_map<int, std::shared_ptr<Model>> models;
    static std::shared_ptr<StageObject> camera;
    static glm::mat4 view;
    static glm::mat4 projection;
    static void renderPolys(Model *model, int polyType);
    static void renderPolys(Model *model, StageObject *stageObject, int polyType);
    static void renderPolys(StagePart *stagePart, int polyType);
    static void renderPolys(const std::vector<std::shared_ptr<StagePart>> &stageParts,
                            int polyType);
    static void render(Stage *stage);
};
#endif