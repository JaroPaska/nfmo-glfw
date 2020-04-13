#include "Get.h"

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

glm::vec3 getvec3(std::string string) {
    return glm::vec3(getfloat(string, 0), getfloat(string, 1), getfloat(string, 2));
}