#include "camera.hpp"

Ray Camera::compute_eye_ray(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {

  Ray ray;

  float inv_width = 1 / static_cast<float>(width);
  float inv_height = 1 / static_cast<float>(height);
  float aspect_ratio = width / float(height);
  float angle = tan(M_PI * 0.5f * fov_ / 180.0f);

  float xx = (2 * ((x + 0.5) * inv_width) - 1) * angle * aspect_ratio;
  float yy = (1 - 2 * ((y + 0.5) * inv_height)) * angle;

  ray.direction_ = glm::normalize(glm::vec3(xx, yy, -1));
  ray.origin_ = pos_;

  return ray;
}