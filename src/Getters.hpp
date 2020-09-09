#ifndef GETTERS_H
#define GETTERS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

int getint(std::string string, int index) {
    std::string t = "";
    int j = -1;
    for (int i = 0; i < string.length(); i++) {
        char c = string[i];
        if (c == '(' || c == ',' || c == ')')
            j++;
        else if (j == index)
            t += c;
    }
    return std::stoi(t);
}

float getfloat(std::string string, int index) {
    std::string t = "";
    int j = -1;
    for (int i = 0; i < string.length(); i++) {
        char c = string[i];
        if (c == '(' || c == ',' || c == ')')
            j++;
        else if (j == index)
            t += c;
    }
    return std::stof(t);
}

std::string getstring(std::string string, int index) {
    std::string t = "";
    int j = -1;
    for (int i = 0; i < string.length(); i++) {
        char c = string[i];
        if (c == '(' || c == ',' || c == ')')
            j++;
        else if (j == index)
            t += c;
    }
    return t;
}

glm::vec3 getvec3(std::string string, int index) {
    return glm::vec3(getfloat(string, index), getfloat(string, index + 1),
                     getfloat(string, index + 2));
}

#endif