#include "RawModel.h"
#include "Stage.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

RawModel::RawModel() {}

RawModel::~RawModel() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void addVertex(glm::vec3 pos, glm::vec3 normal, glm::vec3 centroid, glm::vec3 color,
               std::vector<float> &buffer) {
    for (int i = 0; i < 3; i++)
        buffer.push_back(pos[i]);
    for (int i = 0; i < 3; i++)
        buffer.push_back(normal[i]);
    for (int i = 0; i < 3; i++)
        buffer.push_back(centroid[i]);
    for (int i = 0; i < 3; i++)
        buffer.push_back(color[i]);
}

std::shared_ptr<RawModel> RawModel::ground(float size, int parts) {
    std::vector<std::vector<glm::vec3>> pts(parts + 1, std::vector<glm::vec3>(parts + 1));
    float step = size / parts;
    for (int i = 0; i <= parts; i++)
        for (int j = 0; j <= parts; j++)
            pts[i][j] = glm::vec3(-size / 2 + i * step, 250, -size / 2 + j * step);

    std::vector<float> buffer;
    for (int i = 0; i < parts; i++)
        for (int j = 0; j < parts; j++) {
            glm::vec3 centroid = (pts[i][j] + pts[i + 1][j + 1]) / 2.f;
            addVertex(pts[i][j], Y_AXIS, centroid, glm::vec3(0), buffer);
            addVertex(pts[i + 1][j], Y_AXIS, centroid, glm::vec3(0), buffer);
            addVertex(pts[i][j + 1], Y_AXIS, centroid, glm::vec3(0), buffer);
            addVertex(pts[i][j + 1], Y_AXIS, centroid, glm::vec3(0), buffer);
            addVertex(pts[i + 1][j], Y_AXIS, centroid, glm::vec3(0), buffer);
            addVertex(pts[i + 1][j + 1], Y_AXIS, centroid, glm::vec3(0), buffer);
        }
    std::shared_ptr<RawModel> rawModel = std::make_shared<RawModel>();
    glGenVertexArrays(1, &rawModel->VAO);
    glGenBuffers(1, &rawModel->VBO);
    glBindVertexArray(rawModel->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, rawModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);
    for (int i = 0; i < 4; i++) {
        glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float),
                              (void *)(3 * i * sizeof(float)));
        glEnableVertexAttribArray(i);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    rawModel->vertices = buffer.size() / 12;
    return rawModel;
}