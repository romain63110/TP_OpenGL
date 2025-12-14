#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>

class Drawable {
public:
    Drawable();

    virtual void draw() = 0;
    virtual void set_model_matrix(const glm::mat4& model_matrix);
    virtual void key_handler(int key) = 0;

protected:
    glm::mat4 model_matrix;
};

#endif // DRAWABLE_H
