#include "sphere.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Sphere::~Sphere() {
  std::cout << "Destroyed sphere " + name_ << std::endl;
}

float Sphere::area() const {

  // error -> radius must at least be 0
  if (radius_ < 0.0f) {
    return -1.0f;
  }
  
  return 4.0f * static_cast<float>(M_PI) * pow(radius_, 2);
}

float Sphere::volume() const {

  // error -> radius must at least be 0
  if (radius_ < 0.0f) {
    return -1.0f;
  }

  return (4.0f / 3.0f) * static_cast<float>(M_PI) * pow(radius_, 3);
}

// print sphere object
std::ostream& Sphere::print(std::ostream& os) const {

  std::string middle_point = "[" +
    std::to_string(middle_.x) + ", " + 
    std::to_string(middle_.y) + ", " + 
    std::to_string(middle_.z) +
  "]"; 

  os << std::endl << "Sphere:" << std::endl <<
    "\tMiddle Point: " << middle_point << std::endl <<
    "\tRadius: " << radius_ << std::endl;
    Shape::print(os);

  return os;

}

// test if a ray intersects with the sphere
Hitpoint Sphere::intersect(Ray const& ray, float distance) const {

  // transform ray to local space
  Ray ray_trans = ray.to_local_space(world_transform_inv_);

  // always normalize direction vector
  ray_trans.direction_ = glm::normalize(ray_trans.direction_);

  Hitpoint h;

  h.has_hit_ = glm::intersectRaySphere(ray_trans.origin_, ray_trans.direction_, middle_, pow(radius_, 2), distance);

  if (h.has_hit_) {
    // 3d point at which ray and sphere intersected
    h.intersection_ = ray_trans.origin_ + ray_trans.direction_ * distance;

    // calculate surface normal
    h.normal_ = glm::normalize(h.intersection_ - middle_);

    // distance at which the intersection took place
    h.distance_ = glm::distance(ray_trans.origin_, h.intersection_);

    h.name_ = name_;
    h.color_ = material_->kd_;
    h.ray_direction_ = ray_trans.direction_;

  }

  // transform normal and intersection back to world space
  h.to_world_space(world_transform_, glm::transpose(world_transform_inv_));

  return h;
}

void Sphere::set_middle(glm::vec3 const& middle) {
  middle_ = middle;
}

void Sphere::set_radius(float radius) {
  radius_ = radius;
}
