#include "cone.hpp"

#include <glm/gtx/string_cast.hpp>

float Cone::area() const {
  float slant_height = sqrt(pow(height_, 2.0f) + pow(radius_, 2.0f));
  return PI * radius_ * (slant_height + radius_);
}

float Cone::volume() const {
  return 1.0f / 3.0f * PI * pow(radius_, 2.0f) * height_;
}

std::ostream& Cone::print(std::ostream& os) const {

  os << std::endl << "Cone: " << std::endl <<
    "\tMiddle Point: " << glm::to_string(middle_) << std::endl <<
    "\tRadius: " << radius_ << std::endl <<
    "\tHeight: " << height_ << std::endl;

  Shape::print(os);

  return os;

}

Hitpoint Cone::intersect(Ray const& ray, float distance) const {

  Ray ray_trans = ray.to_local_space(world_transform_inv_);

  ray_trans.direction_ = glm::normalize(ray_trans.direction_);

  Hitpoint h;

  glm::vec3 diff = glm::vec3(middle_.x - ray_trans.origin_.x, middle_.y - ray_trans.origin_.y + height_, middle_.z - ray_trans.origin_.z);

  float a = pow(ray_trans.direction_.x, 2.0f) + pow(ray_trans.direction_.y, 2.0f) + pow(ray_trans.direction_.z, 2.0f);
  float b = diff.x * ray_trans.direction_.x + diff.y * (volume() / height_) * ray_trans.direction_.y + diff.z * ray_trans.direction_.z;
  float c = pow(diff.x, 2.0f) + pow(diff.y, 2.0f) + pow(diff.z, 2.0f);

  float discriminant = pow(b, 2.0f) - a * c;

  if (discriminant > 0) {
    float root_1 = (-1.0f * b - discriminant) / 2.0f - 0.000001;
  }

  h.to_world_space(world_transform_, glm::transpose(world_transform_inv_));

  return h;

}