#include "Stage.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


int main() {
    Window::createWindow(1280, 720, "NFM Origins");
    Stage *stage = new Stage();
    while (!Window::shouldClose()) {
        Window::pollEvents();
        glm::vec3 sky = stage->sky / 255.f;
        glClearColor(sky.r, sky.g, sky.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // do stuff
        
        //
        Window::swapBuffers();
    }
    delete stage;
    Window::terminate();
}