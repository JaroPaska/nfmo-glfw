#include "Loader.h"
#include "Renderer.h"
#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::unique_ptr<Shader> Renderer::polyShader;
std::unordered_map<int, std::unique_ptr<Model>> Renderer::models;
std::unique_ptr<StageObject> Renderer::camera;
glm::mat4 Renderer::view;
glm::mat4 Renderer::projection;

void Renderer::renderPolys(Model *model, int polyType) {
    if (model->polyVAOs[polyType]) {
        glBindVertexArray(model->polyVAOs[polyType]);
        glDrawArrays(GL_TRIANGLES, 0, model->polyVertexCount[polyType]);
    }
}

void Renderer::renderPolys(Model *model, StageObject *stageObject, int polyType) {
    if (model->polyVAOs[polyType]) {
        glm::mat4 uni_model = glm::mat4(1);
        uni_model = glm::translate(uni_model, stageObject->pos);
        uni_model *= glm::mat4(stageObject->rot);
        polyShader->setMat4("uni_model", uni_model);
        polyShader->setMat4("uni_invModel", glm::inverse(uni_model));
        renderPolys(model, polyType);
    }
}

void Renderer::renderPolys(StageObject *stageObject, int polyType) {
    renderPolys(models[stageObject->type].get(), stageObject, polyType);
}

void Renderer::renderPolys(
    const std::unordered_map<int, std::unique_ptr<StageObject>> &stageObjects, int polyType) {
    for (auto it = stageObjects.begin(); it != stageObjects.end(); ++it)
        renderPolys(it->second.get(), polyType);
}

void Renderer::render(Stage *stage) {
    glm::vec3 snap = stage->snap / 100.f;
    glm::vec3 sky = stage->sky / 255.f;
    sky = sky * (glm::vec3(1.f) + snap);
    glm::vec3 fog = stage->fog / 255.f;
    fog = fog * (glm::vec3(1.f) + snap);
    glm::vec3 grnd = stage->grnd / 255.f;
    glm::vec3 glass = stage->sky / 255.f;
    glClearColor(sky.r, sky.g, sky.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    float f = std::max(Window::width, Window::height);
    projection = glm::perspective(glm::radians(60.f), (float)Window::width / (float)Window::height,
                                  100.f / f, 1000000.f / f);
    projection = glm::scale(projection, glm::vec3(1 / f, -1 / f, -1 / f));
    view = glm::mat4(-camera->rot);
    view = glm::translate(view, -camera->pos);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);*/
    polyShader->use();
    glDisable(GL_DEPTH_TEST);
    polyShader->setMat4("uni_projection", projection);
    polyShader->setMat4("uni_view", view);
    polyShader->setMat4("uni_invView", glm::inverse(view));
    glm::mat4 uni_model = glm::mat4(1);
    polyShader->setMat4("uni_model", uni_model);
    polyShader->setMat4("uni_invModel", glm::inverse(uni_model));
    polyShader->setVec3("uni_snap", snap);
    polyShader->setVec3("uni_lightDirection", stage->lightDirection);
    polyShader->setBool("uni_light", false);
    polyShader->setBool("uni_doSnap", true);
    polyShader->setBool("uni_useUniColor", false);
    polyShader->setBool("uni_doFog", false);
    polyShader->setVec3("uni_fog", fog);
    polyShader->setFloat("uni_fadefrom", 3500);
    polyShader->setFloat("uni_density", 0.9);
    renderPolys(stage->groundModel.get(), POLYS_FLAT_COLOR);
    renderPolys(stage->polys1Model.get(), POLYS_FLAT_COLOR);
    renderPolys(stage->polys2Model.get(), POLYS_FLAT_COLOR);
    glEnable(GL_DEPTH_TEST);
    renderPolys(stage->stageObjects, POLYS_FLAT_COLOR);
    polyShader->setBool("uni_useUniColor", true);
    polyShader->setVec3("uni_polyColor", glass);
    renderPolys(stage->stageObjects, POLYS_GLASS);
    polyShader->setBool("uni_light", stage->lightson);
    polyShader->setBool("uni_doSnap", false);
    polyShader->setBool("uni_useUniColor", false);
    renderPolys(stage->stageObjects, POLYS_LIGHT);

    /*projection = glm::perspective(glm::radians(60.f), (float)Window::width /
    (float)Window::height, 750.f / f, 750000.f / f);
    projection = glm::scale(projection, glm::vec3(1 / f, -1 / f, -1 / f));*/
    polyShader->setMat4("uni_projection", projection);
    polyShader->setBool("uni_light", true);
    polyShader->setBool("uni_doSnap", true);
    polyShader->setBool("uni_doFog", false);
    renderPolys(stage->cloudsModel.get(), POLYS_FLAT_COLOR);
    renderPolys(stage->mountainsModel.get(), POLYS_FLAT_COLOR);
}