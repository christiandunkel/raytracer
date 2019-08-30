#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>

#include "shape.hpp"
#include "ray.hpp"

class Sphere : public Shape {

  private:

    glm::vec3 middle_;
    float radius_;

  public:

    Sphere() :
      middle_(glm::vec3(0.0f)), radius_(0.0f) {}

    Sphere(std::string const& name) :
      Shape(name), middle_(glm::vec3(0.0f)), radius_(0.0f) {}

    Sphere(float radius) :
      middle_(glm::vec3(0.0f)), radius_(radius) {}

    Sphere(glm::vec3 middle, float radius) :
      middle_(middle), radius_(radius) {}

    Sphere(glm::vec3 middle, float radius, std::shared_ptr<Material> material) :
      Shape(material), middle_(middle), radius_(radius) {}

    Sphere(glm::vec3 middle, float radius, std::shared_ptr<Material> material, std::string name) :
      Shape(name, material), middle_(middle), radius_(radius) {}

    ~Sphere() override {};

    float area() const override;
    float volume() const override;

    std::ostream& print(std::ostream& os) const override;
    Hitpoint intersect(Ray const& ray, float distance) const override;

    // getter
    glm::vec3 get_middle() const {return middle_;}
    float get_radius() const {return radius_;}

    // setter
    void set_middle(glm::vec3 const& middle) {middle_ = middle;}
    void set_radius(float radius) {radius_ = radius;}

};

#endif // SPHERE_HPP