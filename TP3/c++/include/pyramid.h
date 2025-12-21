#ifndef PYRAMID_H
#define PYRAMID_H

#include "shape.h"
#include "shader.h"
#include <GL/glew.h>


class Pyramid : public Shape {
public:
    Pyramid(Shader* shader_program);
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;
    void key_handler(int key);
    virtual ~Pyramid();

private:
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;

    int num_indices;
};

#endif

