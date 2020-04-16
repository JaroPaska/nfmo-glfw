#include "Loader.h"
#include "Renderer.h"
#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::shared_ptr<Shader> Renderer::polyShader;
std::unordered_map<int, std::shared_ptr<Model>> Renderer::models;
std::shared_ptr<StageObject> Renderer::camera;
glm::mat4 Renderer::view;
glm::mat4 Renderer::projection;

void Renderer::renderPolys(std::shared_ptr<Model> model, std::shared_ptr<StageObject> stageObject,
                           int polyType) {
    if (model->polyVAOs[polyType]) {
        glm::mat4 uni_model = glm::mat4(1.f);
        uni_model = glm::translate(uni_model, stageObject->pos);
        uni_model *= glm::mat4(stageObject->rot);
        polyShader->setMat4("uni_model", uni_model);
        glBindVertexArray(model->polyVAOs[polyType]);
        glDrawArrays(GL_TRIANGLES, 0, model->polyVertexCount[polyType]);
    }
}

void Renderer::renderPolys(std::shared_ptr<StagePart> stagePart, int polyType) {
    renderPolys(models[stagePart->type], stagePart, polyType);
}

void Renderer::renderPolys(std::vector<std::shared_ptr<StagePart>> stageParts, int polyType) {
    for (int i = 0; i < stageParts.size(); i++)
        renderPolys(stageParts[i], polyType);
}

void Renderer::render(std::shared_ptr<Stage> stage) {
    glm::vec3 snap = stage->snap / 100.f;
    glm::vec3 sky = stage->sky / 255.f;
    sky = sky * (glm::vec3(1.f) + snap);
    glm::vec3 fog = stage->fog / 255.f;
    glm::vec3 grnd = stage->grnd / 255.f;
    glm::vec3 glass = stage->sky / 255.f;
    glClearColor(sky.r, sky.g, sky.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    float f = std::max(Window::width, Window::height);
    projection = glm::perspective(glm::radians(60.f), (float)Window::width / (float)Window::height,
                                  100.f / f, 100000.f / f);
    projection = glm::scale(projection, glm::vec3(1 / f, -1 / f, -1 / f));
    view = glm::mat4(-camera->rot);
    view = glm::translate(view, -camera->pos);
    // render ground

    //
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    polyShader->use();
    polyShader->setMat4("uni_projection", projection);
    polyShader->setMat4("uni_view", view);
    polyShader->setVec3("uni_snap", snap);
    polyShader->setBool("uni_light", false);
    polyShader->setBool("uni_useUniColor", false);
    renderPolys(stage->stageParts, POLYS_FLAT_COLOR);
    polyShader->setBool("uni_useUniColor", true);
    polyShader->setVec3("uni_polyColor", glass);
    renderPolys(stage->stageParts, POLYS_GLASS);
    polyShader->setBool("uni_light", true);
    polyShader->setBool("uni_useUniColor", false);
    renderPolys(stage->stageParts, POLYS_LIGHT);
}