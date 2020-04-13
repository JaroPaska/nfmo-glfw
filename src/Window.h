#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    static GLFWwindow *window;
public:
    static void createWindow(int width, int height, const char* title);
    static bool shouldClose();
    static void handleEvents();
    static void swapBuffers();
    static void terminate();
};

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#endif