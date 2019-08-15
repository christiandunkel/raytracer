#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include "color.hpp"

struct Hitpoint {

  bool has_hit_ = false; // if intersection took place
  float distance_ = -1.0f; // distance at which the intersection took place
  std::string name_ = ""; // name of object hit
  Color color_{1.0f, 1.0f, 1.0f}; // color of object hit
  
  // 3d point at which ray and sphere intersected
  glm::vec3 intersection_ = glm::vec3(0.0f);

  // surface normal at intersection
  glm::vec3 normal_ = glm::vec3(0.0f);

  // direction in which the ray was shot
  glm::vec3 ray_direction_{0.0f, 0.0f, 1.0f};

  void transform(glm::mat4 const& mat, glm::mat4 const& trans);
 
};

#endif // define HITPOINT_HPP