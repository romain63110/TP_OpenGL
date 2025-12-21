#include "mesh.h"
#include "shape.h"

#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

Mesh::Mesh(Shader* shader_program, const std::string& path) : Shape(shader_program) {

    Assimp::Importer importer;
    // Options : Triangulate (force les triangles), GenNormals (si absentes)
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERREUR ASSIMP: " << importer.GetErrorString() << std::endl;
        return;
    }

    std::vector<float> vertex_buffer_data;
    std::vector<unsigned int> indices;

    processNode(scene->mRootNode, scene, vertex_buffer_data, indices);

    num_indices = indices.size();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(float), vertex_buffer_data.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);

    // les vecteur normaux => couleur (pour test)
    glEnableVertexAttribArray(1);
    GLintptr offset = 3 * sizeof(GLfloat);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(unsigned int), (GLvoid*)offset);

}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void Mesh::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {

    glUseProgram(this->shader_program_);
    glBindVertexArray(VAO);

    Shape::draw(model, view, projection);

    glDrawElements(GL_TRIANGLES, this->num_indices, GL_UNSIGNED_INT, 0);
}

void Mesh::processNode(aiNode* node, const aiScene* scene, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    // Traiter tous les maillages du nœud
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene, vertices, indices);
    }
    // Traiter les enfants
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, vertices, indices);
    }
}

void Mesh::processMesh(aiMesh* mesh, const aiScene* scene, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    // Current Index Offset (pour fusionner plusieurs meshs en un seul buffer)
    unsigned int offset = vertices.size() / 6;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // POSITION
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        // COULEUR (On utilise les Normales pour simuler de la couleur debug)
        if (mesh->HasNormals()) {
            // On normalise entre 0 et 1 pour que ça fasse des couleurs valides
            vertices.push_back((mesh->mNormals[i].x + 1.0f) * 0.5f);
            vertices.push_back((mesh->mNormals[i].y + 1.0f) * 0.5f);
            vertices.push_back((mesh->mNormals[i].z + 1.0f) * 0.5f);
        }
        else {
            // Rouge par défaut si pas de normales
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(offset + face.mIndices[j]);
    }
}


void Mesh::key_handler(int key) {
    return;
}

