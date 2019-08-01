#include "triangle.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/intersect.hpp>

float Triangle::area() const {
  glm::vec3 ab = b_ - a_;
  glm::vec3 ac = c_ - a_;
  return glm::length(glm::cross(ab, ac)) / 2.0f;
}

float Triangle::volume() const {
  return 0.0f;
}

std::ostream& Triangle::print(std::ostream& os) const {

  std::string point_a = "[" +
    std::to_string(a_.x) + ", " + 
    std::to_string(a_.y) + ", " + 
    std::to_string(a_.z) +
  "]";

  std::string point_b = "[" +
    std::to_string(b_.x) + ", " + 
    std::to_string(b_.y) + ", " + 
    std::to_string(b_.z) +
  "]";

  std::string point_c = "[" +
    std::to_string(c_.x) + ", " + 
    std::to_string(c_.y) + ", " + 
    std::to_string(c_.z) +
  "]";

  os << std::endl << "Triangle:" << std::endl <<
    "\tPoint a: " << point_a << std::endl <<
    "\tPoint b: " << point_b << std::endl <<
    "\tPoint c: " << point_c << std::endl;
    Shape::print(os);

  return os;

}


Hitpoint Triangle::intersect(Ray const &ray, float distance) const {

  Hitpoint h;

  glm::vec2 bary_pos(0.0f);
  
  // TODO: fix intersection method throwing errors
  //h.has_hit_ = glm::intersectRayTriangle(ray.origin_, ray.direction_, a_, b_, c_, bary_pos, distance);

  if (h.has_hit_) {

    // 3d point at which ray and triangle intersected
    glm::vec3 direction_vector = ray.direction_ - ray.origin_;
    glm::vec3 unit_vector(direction_vector / glm::length(direction_vector));
    glm::vec3 intersection_position = unit_vector * distance;
    h.intersection_ = intersection_position;

    // distance at which the intersection took place
    h.distance_ = distance;
  }

  h.name_ = name_;
  h.color_ = material_->kd_;
  h.ray_direction_ = ray.direction_;

  return h;

}