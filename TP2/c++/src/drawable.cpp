#include "drawable.h"

Drawable::Drawable() : model_matrix(glm::mat4(1.0f))
{
}

void Drawable::set_model_matrix(const glm::mat4& model_matrix)
{
    this->model_matrix = model_matrix;
}
