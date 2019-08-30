#ifndef CONE_HPP
#define CONE_HPP

#include "shape.hpp"

class Cone : public Shape {

  private:

    glm::vec3 middle_;
    float radius_;
    float height_;

  public:

    Cone() :
      middle_(glm::vec3(0.0f)), radius_(0.0f), height_(0.0f) {}

    Cone(glm::vec3 const& middle, float radius, float height) :
      middle_(middle), radius_(radius), height_(height) {}

    float area() const override;
    float volume() const override;

    std::ostream& print(std::ostream& os) const override;
    Hitpoint intersect(Ray const& ray, float distance) const override;

    // getter
    glm::vec3 get_middle() const {return middle_;}
    float get_radius() const {return radius_;}
    float get_height() const {return height_;}

    // setter
    void set_middle(glm::vec3 const& middle) {middle_ = middle;}
    void set_radius(float radius) {radius_ = radius;}
    void set_height(float height) {height_ = height;}

};

#endif // CONE_HPP