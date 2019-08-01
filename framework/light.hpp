#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <color.hpp>
#include <string>
#include <glm/vec3.hpp>

struct Light {

  std::string name_;

};

struct AmbientLight : public Light {

  Color color_;
  float intensity_;

};

struct DiffusePointLight : public AmbientLight {

  glm::vec3 pos_;

};

#endif // LIGHT_HPP