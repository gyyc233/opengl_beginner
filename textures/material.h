#ifndef MATERIAL_H
#define MATERIAL_H
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// clang-format on
#include <iostream>


class Material {
public:
    Material(const char* filename);
    ~Material();
    void use();
private:
    unsigned int texture;
};

#endif
