#ifndef SPHERE_H
#define SPHERE_H

#include "drawable.h"
#include "shader.h"
#include <GL/glew.h>

class Sphere : public Drawable {
public:
    Sphere(float radius, int sectors, int stacks, Shader* shader_program);
    void draw();
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

