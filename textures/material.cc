#include "material.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Material::Material(const char *filename) {
  int width, height, channels;
  unsigned char *data =
      stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

  // make the texture
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // load data
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

  // free data
  stbi_image_free(data);

  // Configure sampler
  // 设置环绕模式
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // 设置采样模式
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Material::~Material() { glDeleteTextures(1, &texture); }

void Material::use() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

}