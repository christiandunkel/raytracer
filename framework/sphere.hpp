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
      middle_(glm::vec3(0.0f, 0.0f, 0.0f)), radius_(0.0f) {
        std::cout << "Created sphere " + name_ << std::endl;
      }

    Sphere(std::string name) :
      Shape(name), middle_(glm::vec3(0.0f, 0.0f, 0.0f)), radius_(0.0f) {
        std::cout << "Created sphere " + name_ << std::endl;
      }

    Sphere(float radius) :
      middle_(glm::vec3(0.0f, 0.0f, 0.0f)), radius_(radius) {
        std::cout << "Created sphere " + name_ << std::endl;
      }

    Sphere(glm::vec3 middle, float radius) :
      Shape(), middle_(middle), radius_(radius) {
        std::cout << "Created sphere " + name_ << std::endl;
      }

    Sphere(glm::vec3 middle, float radius, std::shared_ptr<Material> material) :
      Shape(material), middle_(middle), radius_(radius) {
        std::cout << "Created sphere " + name_ << std::endl;
      }

    Sphere(glm::vec3 middle, float radius, std::shared_ptr<Material> material, std::string name) :
      Shape(name, material), middle_(middle), radius_(radius) {
        std::cout << "Created sphere " + name_ << std::endl;
      }

    ~Sphere() override;

    float area() const override;
    float volume() const override;
    std::ostream& Sphere::print(std::ostream& os) const override;
    Hitpoint intersect(Ray const& ray, float distance) const override;

    // getter
    glm::vec3 get_middle() const {return middle_;}
    float get_radius() const {return radius_;}
 
};

#endif // define SPHERE_HPP