#ifndef GET_H
#define GET_H
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int getint(std::string, int index);
float getfloat(std::string, int index);
std::string getstring(std::string, int index);
glm::vec3 getvec3(std::string);
#endif