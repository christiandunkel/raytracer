#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"
#include <string>

#define GLM_EXPERIMENTAL_ENABLED
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class Camera {

  public:

    std::string name_;
    float fov_;
    glm::vec3 pos_;
    glm::vec3 front_;
    glm::vec3 world_up_;

  private:

    glm::vec3 up_;
    glm::vec3 right_;

    float screen_width_;
    float screen_height_;

    float screen_distance;

    void update_vectors();

  public:

    Camera(std::string const& name, float fov, glm::vec3 const& pos, glm::vec3 const& front, glm::vec3 const& world_up) :
      name_(name), fov_(fov), pos_(pos), front_(front), world_up_(world_up) {

        screen_distance = 0.5f / tan(glm::radians(fov_) / 2.0f);

        update_vectors();

      }

    Ray compute_eye_ray(float x, float y);

    glm::mat4 get_view_matrix();

    void set_screen_dimensions(int width, int height);

};

#endif // CAMERA_HPP