#include "Window.h"

#include <cstdlib>
#include <iostream>

GLFWwindow *Window::window;
int Window::width;
int Window::height;

void Window::createWindow(int width, int height, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::exit(-1);
    }
    Window::width = width;
    Window::height = height;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::exit(-1);
    }
    glEnable(GL_MULTISAMPLE);
}

bool Window::shouldClose() { return glfwWindowShouldClose(window); }

void Window::pollEvents() {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::swapBuffers() { glfwSwapBuffers(window); }

void Window::terminate() { glfwTerminate(); }

int Window::getKey(int key) { return glfwGetKey(window, key); }

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    Window::width = width;
    Window::height = height;
}