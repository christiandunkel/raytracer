#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <color.hpp>
#include <string>
#include <glm/vec3.hpp>

class Light {

  public:

    Light() = default;

    Light(std::string const& name) :
      name_(name) {}

    virtual ~Light() = default;

    std::string name_;

};

class AmbientLight : public Light {

  public:

    AmbientLight() :
      color_(1.0f, 1.0f, 1.0f) {}

    AmbientLight(Color const& color, float intensity) :
      color_(color), intensity_(intensity) {}

    AmbientLight(std::string const& name, Color const& color, float intensity) :
      Light(name), color_(color), intensity_(intensity) {}

    virtual ~AmbientLight() = default;

    Color color_;
    float intensity_;

};

class DiffusePointLight : public AmbientLight {

  public:

    DiffusePointLight() = default;

    DiffusePointLight(glm::vec3 const& pos) :
      pos_(pos) {}

    DiffusePointLight(std::string const& name, Color const& color, float intensity, glm::vec3 const& pos) :
      AmbientLight(name, color, intensity), pos_(pos) {}

    glm::vec3 pos_;

};

#endif // LIGHT_HPP