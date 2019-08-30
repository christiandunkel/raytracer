#include "cylinder.hpp"

#include <glm/gtx/string_cast.hpp>

float Cylinder::area() const {
  return 2.0f * PI * pow(radius_, 2.0f) + height_ * (2.0f * PI * radius_);
}

float Cylinder::volume() const {
  return PI * pow(radius_, 2.0f) * height_;
}

std::ostream& Cylinder::print(std::ostream& os) const {

  os << std::endl << "Cone: " << std::endl <<
    "\tMiddle Point: " << glm::to_string(middle_) << std::endl <<
    "\tRadius: " << radius_ << std::endl <<
    "\tHeight: " << height_ << std::endl;

  Shape::print(os);

  return os;

}

Hitpoint Cylinder::intersect(Ray const& ray, float distance) const {

  Ray ray_trans = ray.to_local_space(world_transform_inv_);

  ray_trans.direction_ = glm::normalize(ray_trans.direction_);

  Hitpoint h;

  h.to_world_space(world_transform_, glm::transpose(world_transform_inv_));

  return h;
  
}