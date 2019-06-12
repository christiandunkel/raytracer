#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "sphere.hpp"

Sphere::~Sphere() {
  std::cout << "Destroyed sphere " + name_ << std::endl;
}

float Sphere::area() const {

  // error -> radius must at least be 0
  if (radius_ < 0.0f) {
    return -1.0f;
  }
  
  return 4.0f * M_PI * pow(radius_, 2);
}

float Sphere::volume() const {

  // error -> radius must at least be 0
  if (radius_ < 0.0f) {
    return -1.0f;
  }

  return (4.0f / 3.0f) * M_PI * pow(radius_, 3);
}

// print sphere object
std::ostream& Sphere::print(std::ostream& os) const {
  os << "{\"sphere\":{\n" <<
            "   name: " << name_ << ",\n" <<
            "   middle: {" << 
                    middle_.x << "," <<
                    middle_.y << "," <<
                    middle_.z << 
            "},\n" << 
            "   radius: " << radius_ << ",\n" <<
            "   color: " << color_ <<
        "}}" << std::endl;
  return os;
}

// test if a ray intersects with the sphere
Hitpoint Sphere::intersect(Ray const& ray, float distance) const {

  Hitpoint h;

  h.has_hit_ = glm::intersectRaySphere(ray.origin_, ray.direction_, middle_, pow(radius_, 2), distance);

  if (h.has_hit_) {
    // 3d point at which ray and sphere intersected
    glm::vec3 intersection_position;
    glm::vec3 intersection_normal;
    glm::intersectRaySphere(
      ray.origin_, ray.direction_, middle_, pow(radius_, 2), 
      intersection_position, intersection_normal
    );
    h.intersection_ = intersection_position;

    // distance at which the intersection took place
    h.distance_ = glm::distance(ray.origin_, intersection_position);
  }

  h.name_ = name_;
  h.color_ = color_;
  h.ray_direction_ = ray.direction_;

  return h;

}