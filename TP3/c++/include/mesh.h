#pragma once

#include "shape.h"
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh : public Shape {
public:
    // Le constructeur prend le chemin du fichier 3D
    Mesh(Shader* shader, const std::string& path);
    ~Mesh();
    void key_handler(int key);

    // On surcharge la méthode draw
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;

    int num_indices;

    void processNode(aiNode* node, const aiScene* scene, std::vector<float>& vertices, std::vector<unsigned int>& indices);
    void processMesh(aiMesh* mesh, const aiScene* scene, std::vector<float>& vertices, std::vector<unsigned int>& indices);
};