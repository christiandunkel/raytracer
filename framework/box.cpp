#include "box.hpp"

#include <limits>

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

  Hitpoint hitpoint;

  Ray ray_trans = ray.transform(world_transform_inv_);

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
    return hitpoint;
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
    return hitpoint;
  }

  if (tnear < 0.0f && tfar < 0.0f) {
    return hitpoint;
  }

  hitpoint.intersection_ = ray_trans.origin_ + ray_trans.direction_ * tnear;
  hitpoint.distance_ = glm::distance(hitpoint.intersection_, ray_trans.origin_);

  // calculate normal vector for the respective plane
  if(float_comparison(hitpoint.intersection_.x, min_.x, precision)) {
    hitpoint.normal_ = {-1.0f, 0.0f, 0.0f};
  }
  else if (float_comparison(hitpoint.intersection_.x, max_.x, precision)) {
    hitpoint.normal_ = {1.0f, 0.0f, 0.0f};
  }
  else if (float_comparison(hitpoint.intersection_.y, min_.y, precision)) {
    hitpoint.normal_ = {0.0f, -1.0f, 0.0f};
  }
  else if (float_comparison(hitpoint.intersection_.y, max_.y, precision)) {
    hitpoint.normal_ = {0.0f, 1.0f, 0.0f};
  }
  else if (float_comparison(hitpoint.intersection_.z, min_.z, precision)) {
    hitpoint.normal_ = {0.0f, 0.0f, -1.0f};
  }
  else if (float_comparison(hitpoint.intersection_.z, max_.z, precision)) {
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
