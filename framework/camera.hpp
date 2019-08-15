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
    glm::vec3 pos_;
    glm::vec3 front_;

    float sensitivity_;
    float fov_;

  private:

    glm::vec3 world_up_;
    glm::vec3 up_;
    glm::vec3 right_;

    float yaw_;
    float pitch_;

    float screen_width_;
    float screen_height_;

    float screen_distance;

    void update_vectors();

  public:

    Camera() :
      pos_(glm::vec3(0.0f, 300.0f, 300.0f)),
      front_(glm::vec3(0.0f, -1.0f, -1.0f)),
      sensitivity_(0.06f),
      fov_(20.0f),
      world_up_(glm::vec3(0.0f, 1.0f, 0.0f)),
      yaw_(-90.0f),
      pitch_(0.0f),
      screen_distance(0.0f) {

        float rad = (fov_ * M_PI) / 360;
        screen_distance = 0.5 / (tan(rad));

        update_vectors();
      }

    Ray compute_eye_ray(float x, float y);

    void process_keyboard();
    void update();

    glm::mat4 get_view_matrix();
    glm::mat4 get_projection_matrix() {return glm::perspective(glm::radians(fov_), screen_width_ / screen_height_, 0.1f, 400.0f);}

    void set_screen_dimensions(int width, int height);
};

extern bool key_w;
extern bool key_a;
extern bool key_s;
extern bool key_d;
extern bool key_c;
extern bool key_space;

#endif // CAMERA_HPP