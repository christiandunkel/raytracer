#include "box.hpp"

#include <limits>
#include <algorithm>

const int precision = 10;

// returns true if both values are indentical considering a given precision
bool float_comparison(float a, float b, int precision) {
  return std::abs(a - b) <= std::numeric_limits<float>::epsilon() * std::abs(a + b) * precision || std::abs(a - b) < std::numeric_limits<float>::min();
}

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

  Hitpoint hp;

  // transform ray to local space
  Ray ray_trans = ray.to_local_space(world_transform_inv_);

  // always normalize direction vector
  ray_trans.direction_ = glm::normalize(ray_trans.direction_);

  distance = -1.0f;

  float tmin = (min_.x - ray_trans.origin_.x) / ray_trans.direction_.x;
  float tmax = (max_.x - ray_trans.origin_.x) / ray_trans.direction_.x;
  float tfar = std::max(tmin, tmax);
  float tnear = std::min(tmin, tmax);

  tmin = (min_.y - ray_trans.origin_.y) / ray_trans.direction_.y;
  tmax = (max_.y - ray_trans.origin_.y) / ray_trans.direction_.y;

  if (float_comparison(0.0f, ray_trans.direction_.x, precision)){

    tfar = std::max(tmin, tmax);
    tnear = std::min(tmin, tmax);
  } 
  else {

    tnear = std::max(tnear, std::min(tmin, tmax));
    tfar = std::min(tfar, std::max(tmin, tmax));
  }
  
  if (tnear > tfar) {
    return hp;
  }

  tmin = (min_.z - ray_trans.origin_.z) / ray_trans.direction_.z;
  tmax = (max_.z - ray_trans.origin_.z) / ray_trans.direction_.z;

  if (float_comparison(0.0f, ray_trans.direction_.x, precision) && float_comparison(ray_trans.direction_.y, 0.0f, precision)) {

    tfar = std::max(tmin, tmax);
    tnear = std::min(tmin, tmax);
  }
  else {

    tnear = std::max(tnear, std::min(tmin, tmax));
    tfar = std::min(tfar, std::max(tmin, tmax));
  }
  
  if (tnear > tfar) {
    return hp;
  }

  if (tnear < 0.0f && tfar < 0.0f) {
    return hp;
  }

  hp.intersection_ = ray_trans.origin_ + ray_trans.direction_ * tnear;
  hp.distance_ = glm::distance(hp.intersection_, ray_trans.origin_);

  // calculate normal vector for the respective plane
  if(float_comparison(hp.intersection_.x, min_.x, precision)) {
    hp.normal_ = {-1.0f, 0.0f, 0.0f};
  }
  else if (float_comparison(hp.intersection_.x, max_.x, precision)) {
    hp.normal_ = {1.0f, 0.0f, 0.0f};
  }
  else if (float_comparison(hp.intersection_.y, min_.y, precision)) {
    hp.normal_ = {0.0f, -1.0f, 0.0f};
  }
  else if (float_comparison(hp.intersection_.y, max_.y, precision)) {
    hp.normal_ = {0.0f, 1.0f, 0.0f};
  }
  else if (float_comparison(hp.intersection_.z, min_.z, precision)) {
    hp.normal_ = {0.0f, 0.0f, -1.0f};
  }
  else if (float_comparison(hp.intersection_.z, max_.z, precision)) {
    hp.normal_ = {0.0f, 0.0f, 1.0f};
  }

  hp.has_hit_ = true;
  hp.distance_ = distance;
  hp.color_ = material_->kd_;
  hp.name_ = name_;

  // transform normal and intersection back to world space
  hp.to_world_space(world_transform_, glm::transpose(world_transform_inv_));
  return hp;
}


void Box::set_min(glm::vec3 const& vec) {
  min_ = vec;
}

void Box::set_max(glm::vec3 const& vec) {
  max_ = vec;
}
