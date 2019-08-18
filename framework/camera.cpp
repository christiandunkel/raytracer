#include "camera.hpp"

#include <iostream>

void Camera::update_vectors() {

  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_    = glm::normalize(glm::cross(right_, front_));
  front_ = glm::normalize(front_);
}

Ray Camera::compute_eye_ray(float x, float y) {

  Ray ray;

  ray.origin_ = glm::vec3(0.0f);

  // send ray to screen canvas for each individual pixel
  ray.direction_ = glm::vec3(x, y, -screen_distance);

  // homogeneous coordinates (vec3 to vec4)
  glm::vec4 origin = glm::vec4(ray.origin_, 1);
  glm::vec4 direction = glm::vec4(ray.direction_, 0);

  // transform ray
  origin = get_view_matrix() * origin;
  direction = get_view_matrix() * direction;

  ray.origin_ = origin;
  ray.direction_ = direction;

  return ray;
}

glm::mat4 Camera::get_view_matrix() {

  //if (mouse moved)
    update_vectors();

  // transform to vec4
  glm::vec4 right_h = glm::vec4(right_, 0.0f);
  glm::vec4 up_h    = glm::vec4(up_, 0.0f);
  glm::vec4 front_h = glm::vec4(-front_, -0.0f);
  glm::vec4 pos_h   = glm::vec4(pos_, 1.0f);

  glm::mat4 view_matrix = glm::mat4(right_h, up_h, front_h, pos_h);

  /*
  for further information check out:
  https://www.3dgep.com/understanding-the-view-matrix/
  */

  return view_matrix;
}

void Camera::set_screen_dimensions(int width, int height) {
  screen_width_ = static_cast<float>(width);
  screen_height_ = static_cast<float>(height);
}