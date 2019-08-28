#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "shape.hpp"

class Cylinder : public Shape {

  private:

    glm::vec3 middle_;
    float radius_;
    float height_;

  public:

    Cylinder() :
      middle_(glm::vec3(0.0f)), radius_(0.0f), height_(0.0f) {
        //std::cout << "Created cylinder " << name_ << std::endl;
      }

    Cylinder(glm::vec3 const& middle, float radius, float height) :
      middle_(middle), radius_(radius), height_(height) {
        //std::cout << "Created cylinder " << name_ << std::endl;
      }

    float area() const override;
    float volume() const override;

    std::ostream& print(std::ostream& os) const override;
    Hitpoint intersect(Ray const& ray, float distance) const override;

    glm::vec3 get_middle() const {return middle_;}
    float get_radius() const {return radius_;}
    float get_height() const {return height_;}

    void set_middle(glm::vec3 const& middle);
    void set_radius(float radius);
    void set_height(float height);
};

#endif // CYLINDER_HPP