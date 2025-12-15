#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include "shader.h"
#include <GL/glew.h>

class Sphere : public Shape {
public:
    Sphere(float radius, int sectors, int stacks, Shader* shader_program);
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;
    void key_handler(int key);
    virtual ~Sphere();

private:
    GLuint shader_program_;
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
    int index_count;
};

#endif

