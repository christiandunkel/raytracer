#include "renderer.hpp"
#include "camera.hpp"

#include "sphere.hpp"
#include "box.hpp"
#include "triangle.hpp"

#include <regex>
#include <limits>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

// check if the given renderer instance is valid
bool Renderer::is_valid() {

  if (cam_ == nullptr) {
    std::cerr << "Renderer: Camera points to null in file '" << filename_ << "'." << std::endl;
    return false;
  }

  // test if defined filename has "ppm" ending
  std::regex REGEX_ppm ("^.+\\.ppm$");
  if (!std::regex_match(filename_, REGEX_ppm)) {
    std::cerr << "Renderer: Filename '" << filename_ << "' has no '.ppm' file ending." << std::endl;
    return false;
  }

  return true;

}

void Renderer::render(int flags) {

  float width_f = static_cast<float>(width_);
  float height_f = static_cast<float>(height_);

  for (unsigned y = 0; y < height_; y++) {
    for (unsigned x = 0; x < width_; x++) {

      // reset recursion limit for each new ray
      recursion_limit = initial_recursion_limit;

      Pixel p(x, y);

      // anti aliasing (with 4 sub pixels)
      if (flags & ANTIALIASING) {
      
        for (float w = 0.0f; w < 1.0f; w += 0.5f) {
          for (float h = 0.0f; h < 1.0f; h += 0.5f) {

            recursion_limit = initial_recursion_limit;

            float x_f = static_cast<float>(x + w);
            float y_f = static_cast<float>(y + h);

            // transform pixel position (-0.5, 0.5)
            x_f = (x_f - width_f / 2.0f) / width_f;
            y_f = (y_f - height_f / 2.0f) / width_f;

            Ray eye_ray = cam_->compute_eye_ray(x_f, y_f);
            p.color  += 0.25f * trace(eye_ray);
          }
        }
      }
      // no anti aliasing
      else {

        float x_f = static_cast<float>(x);
        float y_f = static_cast<float>(y);

        // transform pixel position (-0.5, 0.5)
        x_f = (x_f - width_f / 2.0f) / width_f;
        y_f = (y_f - height_f / 2.0f) / width_f;

        Ray eye_ray = cam_->compute_eye_ray(x_f, y_f);
        p.color  += trace(eye_ray);
      }

      write(p);
    }
  }

  // ppm_.save("output/" + filename_);

  // generate a sub folder with date & time as name
  time_t _tm = time(NULL);
  struct tm * curtime = localtime ( &_tm );
  std::string time = asctime(curtime);
  std::replace(time.begin(), time.end(), ':', '-');

  // remove line break if exists
  time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());

  full_path_ = output_directory_ + time + " " + filename_;

  std::cout << "Storing image at: " << full_path_ << std::endl;
  ppm_.save(full_path_);
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

  Color color;

  recursion_limit--;

  // check for intersections with all existing objects
  Hitpoint hp = find_intersection(ray);

  std::shared_ptr<Shape> hit_shape = nullptr;

  // find shape that has been hit by a ray
  hit_shape = root_->find_shape(hp.name_);

  /*
  OPTIONAL:
    add refraction
    add cylinder and cone
  */

  if (hit_shape != nullptr) {

    std::shared_ptr<Material> material = hit_shape->get_material();

    static float attenuation = 1.0f;

    if (material->refraction_index_ == 0.0f) {

      // iterate over all existing light sources
      for (auto const light : *lights_) {

        // test if diffuse point light
        if (dynamic_cast<DiffusePointLight*>(light.get())) {

          // cast light pointer to DiffusePointLight pointer
          auto point_light_ptr = std::static_pointer_cast<DiffusePointLight>(light);

          // calculate direction of light
          glm::vec3 light_direction = glm::normalize(point_light_ptr->pos_ - hp.intersection_);

          // ray starting at the light's origin
          Ray light_ray{hp.intersection_ + light_direction, light_direction};

          Hitpoint hp_light = find_intersection(light_ray);

          // ambient
          static float ambient_intensity = point_light_ptr->intensity_;
          Color ambient = ambient_intensity * material->ka_ * point_light_ptr->color_;

          // diffuse
          float diff = glm::max(glm::dot(hp.normal_, light_direction), 0.0f);
          Color diffuse = diff * material->kd_;

          // specular
          glm::vec3 view_direction = glm::normalize(cam_->pos_ - hp.intersection_);
          glm::vec3 reflection_direction = glm::reflect(-light_direction, hp.normal_);

          glm::vec3 halfway_direction = glm::normalize(light_direction + view_direction);
          float spec = pow(glm::max(glm::dot(hp.normal_, halfway_direction), 0.0f), material->m_);

          Color specular = spec * material->ks_;

          // light attenuation
          const float light_constant = 1.0f;
          static float light_linear = 0.09f;
          static float light_quadratic = 0.032f;

          float light_distance = glm::length(glm::normalize(point_light_ptr->pos_ - hp.intersection_));
          attenuation = 1.0f / (light_constant + light_linear * light_distance + light_quadratic * pow(light_distance, 2));

          ambient *= attenuation;
          diffuse *= attenuation;
          specular *= attenuation;

          // test if there's no obstacle between light and object
          if (!hp_light.has_hit_) {
            // combine all colors
            color += ambient + diffuse + specular;
          }
          else {
            // object is in shadow
            color += ambient;
          }

        }
        else if (dynamic_cast<AmbientLight*>(light.get())) {

          // cast light pointer to AmbientLight pointer
          auto ambient_light_ptr = std::static_pointer_cast<AmbientLight>(light);

          // ambient
          static float ambient_intensity = ambient_light_ptr->intensity_;
          Color ambient = ambient_intensity * material->ka_ * ambient_light_ptr->color_;
          ambient *= attenuation;

          // only add ambient to final color
          color += ambient;

        }
      }
    }

    if (recursion_limit > 0) {

      // reflection if reflection coefficient and refraction index aren't zero
      if (material->r_ != 0.0f && material->refraction_index_ == 0.0f) {

        glm::vec3 reflection = glm::normalize(glm::reflect(ray.direction_, hp.normal_));
        Color color_reflected = trace(Ray{hp.intersection_ + reflection, reflection});

        color += material->r_ * color_reflected;

      }
    }
  }
  else {
    // return background color
    return background_;
  }

  // apply tone mapping (basic HDR, maybe?)
  color.r = color.r / (color.r + 1);
  color.g = color.g / (color.g + 1);
  color.b = color.b / (color.b + 1);

  // perform gamma correction
  const float gamma = 2.2f;
  glm::vec3 gamma_corrected = pow(glm::vec3(color.r, color.g, color.b), glm::vec3(1.0f / gamma));
  color = Color{gamma_corrected.x, gamma_corrected.y, gamma_corrected.z};

  return color;

}

Hitpoint Renderer::find_intersection(Ray const& ray) {

  Hitpoint first_hit;
  first_hit.distance_ = std::numeric_limits<float>::max();

  root_->find_intersection(first_hit, ray);

  return first_hit;
  
}