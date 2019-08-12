#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"
#include <string>
#include <glm/vec3.hpp>

class Camera {

  public:

    Camera() :
      pos_(glm::vec3(0.0f)), fov_(45.0f) {}
    Camera(std::string const& name, glm::vec3 const& pos, float fov) :
      name_(name), pos_(pos), fov_(fov) {}

    Ray compute_eye_ray(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    std::string name_;
    glm::vec3 pos_;
    float fov_;

};

#endif // CAMERA_HPP