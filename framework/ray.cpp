#include "ray.hpp"

// transform to homogeneous coordinates 
Ray Ray::to_local_space(glm::mat4 const& mat) const {

  // 3D point becomes (x,y,z,1)
  glm::vec3 origin = glm::vec3(mat * glm::vec4(origin_, 1.0f));

  // 3D vector becomes (x,y,z,0) since it is the difference between two 3D points
  glm::vec3 direction = glm::vec3(mat * glm::vec4(direction_, 0.0f));

  return Ray{origin, direction};
}