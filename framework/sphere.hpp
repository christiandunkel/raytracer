#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>

#include "shape.hpp"

class Sphere : public Shape {

  private:

    glm::vec3 middle_;
    float radius_;

  public:

    Sphere() :
      middle_(glm::vec3(0.0f, 0.0f, 0.0f)), radius_(0.0f) {}

    Sphere(float radius) :
      middle_(glm::vec3(0.0f, 0.0f, 0.0f)), radius_(radius) {}

    Sphere(glm::vec3 middle, float radius) :
      middle_(middle), radius_(radius) {}

    virtual float area() const override;
    virtual float volume() const override;

    glm::vec3 get_middle() {return middle_;}
    float get_radius() {return radius_;}
 
};

#endif // define SPHERE_HPP