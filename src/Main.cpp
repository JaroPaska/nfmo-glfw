#include "Renderer.h"
#include "Stage.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "Get.h"

int main() {
    Window::createWindow(1280, 720, "NFM Origins");
    Renderer::loadShaders();
    Renderer::loadModels();
    std::shared_ptr<Stage> stage(new Stage("stages/2.txt"));
    while (!Window::shouldClose()) {
        Window::pollEvents();
        // do stuff
        Renderer::render(stage);
        //
        Window::swapBuffers();
    }
    Window::terminate();
}