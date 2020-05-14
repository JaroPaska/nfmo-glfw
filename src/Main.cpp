#include "Loader.h"
#include "Renderer.h"
#include "Stage.h"
#include "Window.h"

int main() {
    Window::createWindow(1600, 900, "NFM Origins");
    Loader::loadShaders();
    Loader::loadModels();
    Renderer::camera = std::make_shared<StageObject>();

    std::shared_ptr<Stage> stage = std::make_shared<Stage>("stages/26");
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
        Renderer::render(stage.get());
        //
        Window::swapBuffers();
    }
    Window::terminate();
}
