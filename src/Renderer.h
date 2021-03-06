#ifndef RENDERER_H
#define RENDERER_H
#include "Model.h"
#include "Shader.h"
#include "Stage.h"
#include "StageObject.h"
#include <memory>
#include <unordered_map>

struct Renderer {
    static std::unique_ptr<Shader> polyShader;
    static std::unordered_map<int, std::unique_ptr<Model>> models;
    static std::unique_ptr<StageObject> camera;
    static glm::mat4 view;
    static glm::mat4 projection;
    static void renderPolys(Model *model, int polyType);
    static void renderPolys(Model *model, StageObject *stageObject, int polyType);
    static void renderPolys(StageObject *stageObject, int polyType);
    static void
    renderPolys(const std::unordered_map<int, std::unique_ptr<StageObject>> &stageObjects,
                int polyType);
    static void render(Stage *stage);
};
#endif