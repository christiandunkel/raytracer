#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>

class Camera {

  std::string name_;
  glm::vec3 pos_;
  float fov_;

};

#endif // CAMERA_HPP