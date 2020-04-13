#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    static GLFWwindow *window;
    static int width, height;
public:
    static void createWindow(int width, int height, const char* title);
    static bool shouldClose();
    static void pollEvents();
    static void swapBuffers();
    static void terminate();
    static int getKey(int key);
    static int getWidth();
    static int getHeight();
    static void setWidth(int width);
    static void setHeight(int height);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#endif