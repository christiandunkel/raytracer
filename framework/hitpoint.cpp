#include "hitpoint.hpp"

void Hitpoint::to_world_space(glm::mat4 const& mat, glm::mat4 const& mat_inv_trans) {

  intersection_ = glm::vec3(mat * glm::vec4(intersection_, 1.0f));
  normal_ = glm::normalize(glm::vec3(mat_inv_trans * glm::vec4(normal_, 0.0f)));
}