#include "ray.hpp"

// transform to homogeneous coordinates 
Ray Ray::transform(glm::mat4 const& mat) const {

  glm::vec4 origin = mat * glm::vec4(origin_, 1.0f);
  glm::vec4 direction = mat * glm::vec4(direction_, 0.0f);

  return Ray{glm::vec3(origin), glm::vec3(direction)};
}