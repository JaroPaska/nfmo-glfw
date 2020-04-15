#include "Loader.h"
#include "Renderer.h"
#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::shared_ptr<Shader> Renderer::polyShader;
std::unordered_map<int, std::shared_ptr<Model>> Renderer::models;
std::shared_ptr<StageObject> camera;
glm::mat4 Renderer::view;
glm::mat4 Renderer::projection;

void Renderer::renderPolys(std::shared_ptr<StagePart> stagePart, int polyType) {
    if (models[stagePart->type]->polyVAOs[polyType]) {
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, stagePart->pos);
        model *= glm::mat4(stagePart->rot);
        polyShader->setMat4("uni_model", model);
        glBindVertexArray(models[stagePart->type]->polyVAOs[polyType]);
        glDrawArrays(GL_TRIANGLES, 0, models[stagePart->type]->polyVertexCount[polyType]);
    }
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
    projection = glm::perspective(glm::radians(90.f), (float)Window::width / (float)Window::height,
                                  100.f / f, 100000.f / f);
    projection = glm::scale(projection, glm::vec3(1 / f, -1 / f, -1 / f));
    view = glm::mat4(1.f);
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
    for (int i = 0; i < stage->stageParts.size(); i++)
        renderPolys(stage->stageParts[i], POLYS_FLAT_COLOR);
}