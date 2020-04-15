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
    static void renderPolys(std::shared_ptr<Model> model, std::shared_ptr<StageObject> stageObject,
                            int polyType);
    static void renderPolys(std::shared_ptr<StagePart> stagePart, int polyType);
    static void renderPolys(std::vector<std::shared_ptr<StagePart>> stageParts, int polyType);
    static void render(std::shared_ptr<Stage> stage);
};
#endif