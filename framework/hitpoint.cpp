#include "hitpoint.hpp"

void Hitpoint::transform(glm::mat4 const& mat, glm::mat4 const& trans) {

  intersection_ = glm::vec3(mat * glm::vec4(intersection_, 1.0f));
  normal_ = glm::normalize(glm::vec3(mat * glm::vec4(normal_, 0.0f)));
}