#include "box.hpp"

#include <catch.hpp>

Box::~Box() {
  std::cout << "Destroyed box " + name_ << std::endl;
}

float Box::area() const {
  // area = 2*l*w + 2*l*h + 2*w*h
  float side_x = max_.x - min_.x,
        side_y = max_.y - min_.y,
        side_z = max_.z - min_.z;
  return 2 * (side_x * side_y + 
              side_y * side_z + 
              side_x * side_z);
}

float Box::volume() const {
  // volume = length * width * height
  float side_x = max_.x - min_.x,
        side_y = max_.y - min_.y,
        side_z = max_.z - min_.z;
  return side_x * side_y * side_z;
}

// print box object
std::ostream& Box::print(std::ostream& os) const {

  std::string min_point = "[" + 
      std::to_string(min_.x) + ", " + 
      std::to_string(min_.y) + ", " + 
      std::to_string(min_.z) + 
    "]";

  std::string max_point = "[" + 
      std::to_string(max_.x) + ", " + 
      std::to_string(max_.y) + ", " + 
      std::to_string(max_.z) + 
    "]";

  os << std::endl << "Box:" << std::endl <<
        "Min Point: " << min_point << std::endl <<
        "Max Point: " << max_point << std::endl;
        Shape::print(os);

  return os;
}

Hitpoint Box::intersect(Ray const &ray, float distance) const {

  Hitpoint hitpoint;

  Ray ray_trans = ray.transform(world_transform_inv_);

  distance = -1.0f;

  float tmin = (min_.x - ray_trans.origin_.x) / ray_trans.direction_.x;
  float tmax = (max_.x - ray_trans.origin_.x) / ray_trans.direction_.x;
  float tfar = std::max(tmin, tmax);
  float tnear = std::min(tmin, tmax);

  tmin = (min_.y - ray_trans.origin_.y) / ray_trans.direction_.y;
  tmax = (max_.y - ray_trans.origin_.y) / ray_trans.direction_.y;

  if (ray_trans.direction_.x == Approx(0.0f)){

    tfar = std::max(tmin, tmax);
    tnear = std::min(tmin, tmax);
  } 
  else {

    tnear = std::max(tnear, std::min(tmin, tmax));
    tfar = std::min(tfar, std::max(tmin, tmax));
  }
  
  if (tnear > tfar) {
    return hitpoint;
  }

  tmin = (min_.z - ray_trans.origin_.z) / ray_trans.direction_.z;
  tmax = (max_.z - ray_trans.origin_.z) / ray_trans.direction_.z;

  if (ray_trans.direction_.x == Approx(0.0f) && ray_trans.direction_.y == Approx(0.0f)) {

    tfar = std::max(tmin, tmax);
    tnear = std::min(tmin, tmax);
  }
  else {

    tnear = std::max(tnear, std::min(tmin, tmax));
    tfar = std::min(tfar, std::max(tmin, tmax));
  }
  
  if (tnear > tfar) {
    return hitpoint;
  }

  if (tnear < 0.0f && tfar < 0.0f) {
    return hitpoint;
  }

  hitpoint.distance_ = tnear * sqrt(ray_trans.direction_.x * ray_trans.direction_.x + ray_trans.direction_.y * ray_trans.direction_.y + ray_trans.direction_.z * ray_trans.direction_.z);
  hitpoint.intersection_ = ray_trans.origin_ + ray_trans.direction_ * tnear;

  // calculate normal vector for the respective plane
  if(hitpoint.intersection_.x == Approx(min_.x)) {
    hitpoint.normal_ = {-1.0f, 0.0f, 0.0f};
  }
  else if (hitpoint.intersection_.x == Approx(max_.x)) {
    hitpoint.normal_ = {1.0f, 0.0f, 0.0f};
  }
  else if (hitpoint.intersection_.y == Approx(min_.y)) {
    hitpoint.normal_ = {0.0f, -1.0f, 0.0f};
  }
  else if (hitpoint.intersection_.y == Approx(max_.y)) {
    hitpoint.normal_ = {0.0f, 1.0f, 0.0f};
  }
  else if (hitpoint.intersection_.z == Approx(min_.z)) {
    hitpoint.normal_ = {0.0f, 0.0f, -1.0f};
  }
  else if (hitpoint.intersection_.z == Approx(max_.z)) {
    hitpoint.normal_ = {0.0f, 0.0f, 1.0f};
  }

  hitpoint.has_hit_ = true;
  hitpoint.distance_ = distance;
  hitpoint.color_ = material_->kd_;
  hitpoint.name_ = name_;

  hitpoint.transform(world_transform_);
  return hitpoint;
}


void Box::set_min(glm::vec3 const& vec) {
  min_ = vec;
}

void Box::set_max(glm::vec3 const& vec) {
  max_ = vec;
}
