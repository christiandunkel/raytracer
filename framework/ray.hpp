#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

struct Ray {

  glm::vec3 origin_{0.0f, 0.0f, 0.0f};
  glm::vec3 direction_{0.0f, 0.0f, -1.0f};

  Ray to_local_space(glm::mat4 const& mat) const;

};

#endif // RAY_HPP