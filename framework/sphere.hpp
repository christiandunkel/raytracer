#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>

#include "color.hpp"
#include "shape.hpp"

class Sphere : public Shape {

  private:

    glm::vec3 middle_;
    float radius_;

  public:

    Sphere() :
      Shape(), middle_(glm::vec3(0.0f, 0.0f, 0.0f)), radius_(0.0f) {}

    Sphere(std::string name) :
      Shape(name), middle_(glm::vec3(0.0f, 0.0f, 0.0f)), radius_(0.0f) {}

    Sphere(float radius) :
      Shape(), middle_(glm::vec3(0.0f, 0.0f, 0.0f)), radius_(radius) {}

    Sphere(glm::vec3 middle, float radius) :
      Shape(), middle_(middle), radius_(radius) {}

    Sphere(Color color, glm::vec3 middle, float radius) :
      Shape(color), middle_(middle), radius_(radius) {}

    Sphere(std::string name, Color color, glm::vec3 middle, float radius) :
      Shape(name, color), middle_(middle), radius_(radius) {}

    virtual float area() const override;
    virtual float volume() const override;

    // getter
    std::string get_name() const {return name_;}
    Color get_color() const {return color_;}
    glm::vec3 get_middle() const {return middle_;}
    float get_radius() const {return radius_;}
 
};

#endif // define SPHERE_HPP