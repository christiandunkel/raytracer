#include "renderer.hpp"
#include "camera.hpp"

#include "sphere.hpp"
#include "box.hpp"
#include "triangle.hpp"

#include <regex>
#include <limits>

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

  Color color = Color(0.2f, 0.2f, 0.2f);

  // check for intersections with all existing objects
  Hitpoint hp = find_intersection(ray);

  std::shared_ptr<Shape> hit_shape = nullptr;

  // find shape that has been hit by a ray
  for (auto const shape : (*shapes_)) {
    
    if (shape->get_name() == hp.name_) {
      hit_shape = shape;
    }
  }

  /*
  TODO:
    add refraction and mirroring
    update triangle and box intersection methods
    add transformation to parser
  */

  if (hit_shape != nullptr) {

    std::shared_ptr<Material> material = hit_shape->get_material();

    static float attenuation = 1.0f;

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

        Hitpoint hp_light = find_intersection(light_ray);

        // ambient
        static float ambient_intensity = point_light_ptr->intensity_;
        Color ambient = ambient_intensity * material->ka_ * point_light_ptr->color_;

        // diffuse
        float diff = glm::max(glm::dot(hp.normal_, light_direction), 0.0f);
        Color diffuse = diff * material->kd_;

        // specular
        glm::vec3 view_direction = glm::normalize(cam_->pos_ -hp.intersection_);
        glm::vec3 reflection_direction = glm::reflect(-light_direction, hp.normal_);

        glm::vec3 halfway_direction = glm::normalize(light_direction + view_direction);
        float spec = pow(glm::max(glm::dot(hp.normal_, halfway_direction), 0.0f), material->m_);

        Color specular = spec * material->ks_ ;

        // light attenuation
        const float light_constant = 1.0f;
        static float light_linear = 0.09f;
        static float light_quadratic = 0.032f;

        float light_distance = glm::length(point_light_ptr->pos_ - hp.intersection_);
        attenuation = 1.0f / (light_constant + light_linear * light_distance + light_quadratic * pow(light_distance, 2));

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        if (!hp_light.has_hit_) {
          // combine all colors
          color += ambient + diffuse + specular;
        }
        else {
          // in shadow
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

  return color;
}

Hitpoint Renderer::find_intersection(Ray const& ray) {

  Hitpoint first_hit;
  first_hit.distance_ = std::numeric_limits<float>::max();

  for(auto const shape : *shapes_){

    Hitpoint hit = shape->intersect(ray);

    if (hit.has_hit_) {

      hit.distance_ = glm::distance(hit.intersection_, ray.origin_);

      if (first_hit.distance_ > hit.distance_) {
        first_hit = hit;
      }
    }

  }

  return first_hit;
}