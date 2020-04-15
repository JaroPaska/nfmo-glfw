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
    while (!Window::shouldClose()) {
        Window::pollEvents();
        // do stuff
        Renderer::render(stage);
        //
        Window::swapBuffers();
    }
    Window::terminate();
}