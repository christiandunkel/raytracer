#include "camera.hpp"

#include <iostream>

void Camera::update_vectors() {

  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_    = glm::normalize(glm::cross(right_, front_));
  front_ = glm::normalize(front_);

}

// generate ray from camera to view plane
Ray Camera::compute_eye_ray(float x, float y) {

  // transform pixel position (-0.5, 0.5)
  x = (x - screen_width_ / 2.0f) / screen_width_;
  y = (y - screen_height_ / 2.0f) / screen_width_;

  Ray ray;

  // send ray to screen canvas for each individual pixel
  ray.direction_ = glm::vec3(x, y, -screen_distance);

  // transform ray
  ray.origin_ = get_view_matrix() * glm::vec4(ray.origin_, 1.0f);
  ray.direction_ = get_view_matrix() * glm::vec4(ray.direction_, 0.0f);

  return ray;

}

glm::mat4 Camera::get_view_matrix() {

  /* more info: https://www.3dgep.com/understanding-the-view-matrix/ */

  // transform to vec4 homogeneous vectors
  glm::vec4 right_h = glm::vec4(right_, 0.0f);
  glm::vec4 up_h    = glm::vec4(up_, 0.0f);
  glm::vec4 front_h = glm::vec4(-front_, 0.0f);
  glm::vec4 pos_h   = glm::vec4(pos_, 1.0f);

  glm::mat4 view_matrix = glm::mat4(right_h, up_h, front_h, pos_h);

  return view_matrix;

}

void Camera::set_screen_dimensions(int width, int height) {

  screen_width_ = static_cast<float>(width);
  screen_height_ = static_cast<float>(height);

}