#include "Loader.h"
#include "Renderer.h"
#include "Stage.h"
#include "Window.h"

int main() {
    Window::createWindow(1280, 720, "NFM Origins");
    Loader::loadShaders();
    Loader::loadModels();
    Renderer::camera = std::shared_ptr<StageObject>(new StageObject());

    std::shared_ptr<Stage> stage(new Stage("stages/18.txt"));
    stage->groundModel = RawModel::ground(200000.f, 8);
    while (!Window::shouldClose()) {
        Window::pollEvents();
        // do stuff
        if (Window::getKey(GLFW_KEY_BACKSPACE))
            Renderer::camera->pos.y -= 10.f;
        if (Window::getKey(GLFW_KEY_ENTER))
            Renderer::camera->pos.y += 10.f;
        if (Window::getKey(GLFW_KEY_LEFT))
            Renderer::camera->rot = glm::rotate(Renderer::camera->rot, -0.02f, Y_AXIS);
        if (Window::getKey(GLFW_KEY_RIGHT))
            Renderer::camera->rot = glm::rotate(Renderer::camera->rot, 0.02f, Y_AXIS);
        if (Window::getKey(GLFW_KEY_UP)) {
            glm::vec3 v = glm::vec3(glm::mat4(Renderer::camera->rot) * glm::vec4(0, 0, 100, 1));
            v.x = -v.x; // why the fuck is this necessary
            Renderer::camera->pos += v;
        }
        if (Window::getKey(GLFW_KEY_DOWN)) {
            glm::vec3 v = glm::vec3(glm::mat4(Renderer::camera->rot) * glm::vec4(0, 0, 100, 1));
            v.x = -v.x;
            Renderer::camera->pos -= v;
        }
        Renderer::render(stage);
        //
        Window::swapBuffers();
    }
    Window::terminate();
}
