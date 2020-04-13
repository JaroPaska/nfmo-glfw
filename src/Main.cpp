#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


int main() {
    Window::createWindow(1280, 720, "NFM Origins");
    while (!Window::shouldClose()) {
        Window::handleEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // do stuff

        //
        Window::swapBuffers();
    }
    Window::terminate();
}