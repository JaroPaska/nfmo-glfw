#include "Stage.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


int main() {
    Window::createWindow(1280, 720, "NFM Origins");
    Stage *stage = new Stage(1);
    while (!Window::shouldClose()) {
        Window::pollEvents();
        glClearColor(stage->sky.r, stage->sky.g, stage->sky.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // do stuff
        
        //
        Window::swapBuffers();
    }
    delete stage;
    Window::terminate();
}