#include "renderer.hpp"
#include "camera.hpp"

#include "sphere.hpp"
#include "box.hpp"
#include "triangle.hpp"

#include <regex>

Color scene_ambient = Color(0.2f, 0.2f, 0.2f);

// check if the given renderer instance is valid
bool Renderer::is_valid() {

  if (cam_ == nullptr) {
    std::cout << "Renderer: Camera points to null for '" << filename_ << "' renderer." << std::endl;
    return false;
  }

  // test if defined filename has "ppm" ending
  std::regex REGEX_ppm ("^.+\\.ppm$");
  if (!std::regex_match(filename_, REGEX_ppm)) {
    std::cout << "Renderer: Given filename '" << filename_ << "' has no '.ppm' file ending." << std::endl;
    return false;
  }

  return true;

}

void Renderer::render() {

  float width_f = static_cast<float>(width_);
  float height_f = static_cast<float>(height_);

  for (unsigned y = 0; y < height_; y++) {
    for (unsigned x = 0; x < width_; x++) {

      Pixel p(x, y);

      float x_f = static_cast<float>(x);
      float y_f = static_cast<float>(y);

      x_f = (x_f - width_f / 2.0f) / width_f;
      y_f = (y_f - height_f / 2.0f) / width_f;

      Ray eye_ray = cam_->compute_eye_ray(x_f, y_f);

      p.color = trace(eye_ray);

      write(p);
    }
  }

  ppm_.save("output/" + filename_);

/*
  // generate a sub folder with date & time as name
  time_t _tm =time(NULL );
  struct tm * curtime = localtime ( &_tm );
  std::string time = asctime(curtime);
  std::replace(time.begin(), time.end(), ':', '-');

  ppm_.save("output/" + time + " " + filename_);
*/

}

void Renderer::write(Pixel const& p) {

  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } 
  else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);

}

Color Renderer::trace(Ray const& ray) {

  Color color = scene_ambient;

  // check for intersections with all existing objects
  float closest_d = 0.0f;
  std::shared_ptr<Shape> closest_s = nullptr;

  Hitpoint hp;

  for (auto const shape : *shapes_) {

    hp = shape->intersect(ray, closest_d);

    if (hp.distance_ > closest_d) {
      closest_d = hp.distance_;
      closest_s = shape;
    }
  }

  if (closest_s != nullptr) {

    std::shared_ptr<Material> material = closest_s->get_material();

    // iterate over all existing light sources
    for (auto const light : *lights_) {

      if (dynamic_cast<DiffusePointLight*>(light.get()))
      {
        // cast light pointer to DiffusePointLight pointer
        auto point_light_ptr = std::static_pointer_cast<DiffusePointLight>(light);

        // calculate direction of light
        glm::vec3 light_direction = glm::normalize(point_light_ptr->pos_ - hp.intersection_);

        // ray starting at the light's origin
        Ray light_ray{hp.intersection_ + light_direction, light_direction};

        Hitpoint hp_light;

        // check for intersection with current light
        float closest_d = 0.0f;
        std::shared_ptr<Shape> closest_s = nullptr;

        for (auto const shape : *shapes_) {

          hp_light = shape->intersect(light_ray, closest_d);

          if (hp.distance_ > closest_d) {
            closest_d = hp.distance_;
            closest_s = shape;
          }
        }

        // ambient
        Color ambient{0.0f, 0.0f, 0.0f};

        static float ambient_intensity = 0.05f;

        ambient.r = ambient_intensity * material->ka_.r * scene_ambient.r;
        ambient.g = ambient_intensity * material->ka_.g * scene_ambient.g;
        ambient.b = ambient_intensity * material->ka_.b * scene_ambient.b;

        // diffuse
        Color diffuse{0.0f, 0.0f, 0.0f};

        float diff = glm::max(glm::dot(hp.normal_, light_direction), 0.0f);

        diffuse.r = diff * closest_s->get_material()->kd_.r;
        diffuse.g = diff * closest_s->get_material()->kd_.g;
        diffuse.b = diff * closest_s->get_material()->kd_.b;

        // specular
        Color specular{0.0f, 0.0f, 0.0f};

        glm::vec3 view_direction = glm::normalize(cam_->pos_ -hp.intersection_);
        glm::vec3 reflection_direction = glm::reflect(-light_direction, hp.normal_);

        glm::vec3 halfway_direction = glm::normalize(light_direction + view_direction);
        float spec = glm::pow(glm::max(glm::dot(hp.normal_, halfway_direction), 0.0f), 32.0f);

        specular.r = spec * material->ks_.r;
        specular.g = spec * material->ks_.g;
        specular.b = spec * material->ks_.b;

        if (!hp_light.has_hit_) {
          // combine all colors
          color.r = ambient.r + diffuse.r + specular.r;
          color.g = ambient.g + diffuse.g + specular.g;
          color.b = ambient.b + diffuse.b + specular.b;
        }
        else {
          color.r = ambient.r;
          color.g = ambient.g;
          color.b = ambient.b;
        }
      }
    }
  }

  return color;
}