#include "box.hpp"

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

  // member variables of box object
  hitpoint.name_ = name_;
  hitpoint.color_ = material_->kd_;
  hitpoint.ray_direction_ = ray.direction_;

  float tmin = (min_.x - ray.origin_.x) / ray.direction_.x; 
  float tmax = (max_.x - ray.origin_.x) / ray.direction_.x; 

  if (tmin > tmax) {
    std::swap(tmin, tmax);
  } 

  float tymin = (min_.y - ray.origin_.y) / ray.direction_.y;
  float tymax = (max_.y - ray.origin_.y) / ray.direction_.y;

  if (tymin > tymax) {
    std::swap(tymin, tymax); 
  }

  if (tmin > tymax || tymin > tmax) {
    hitpoint.has_hit_ = false;
  }
  else {

    if (tymin > tmin) {
      tmin = tymin;
    }  

    if (tymax < tmax) { 
      tmax = tymax;
    }

    float tzmin = (min_.z - ray.origin_.z) / ray.direction_.z; 
    float tzmax = (max_.z - ray.origin_.z) / ray.direction_.z; 

    if (tzmin > tzmax) {
      std::swap(tzmin, tzmax); 
    }

    if (tmin > tzmax || tzmin > tmax) { 
      hitpoint.has_hit_ = false;
    }
    else {

      if (tzmin > tmin) { 
        tmin = tzmin;
      }

      if (tzmax < tmax) {
        tmax = tzmax;
      }

      hitpoint.has_hit_ = true;
      hitpoint.intersection_ = glm::vec3{
        tmin * ray.direction_.x + ray.origin_.x, 
        tmin * ray.direction_.y + ray.origin_.y, 
        tmin * ray.direction_.z + ray.origin_.z
      };
      hitpoint.distance_ = glm::distance(ray.origin_, hitpoint.intersection_);

    }

  }

  return hitpoint;

}

void Box::set_min(glm::vec3 const& vec) {
  min_ = vec;
}

void Box::set_max(glm::vec3 const& vec) {
  max_ = vec;
}
