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

glm::vec3 refract(glm::vec3 const& direction, glm::vec3 const& normal, float ior) {

  float cosi = glm::clamp(glm::dot(direction, normal), -1.0f, 1.0f);
  float etai = 1.0f;
  float etat = ior;

  glm::vec3 n = normal;

  if (cosi < 0.0f) {
    cosi = -cosi;
  }
  else {
    std::swap(etai, etat);
    n = -normal;
  }

  float eta = etai / etat;
  float k = 1.0f - pow(eta, 2.0f) * (1.0f - pow(cosi, 2.0f));

  return eta * direction + (eta * cosi - sqrtf(k)) * n;

}

float fresnel(glm::vec3 const& direction, glm::vec3 const& normal, float ior) {

  float cosi = glm::clamp(glm::dot(direction, normal), -1.0f, 1.0f);
  float etai = 1.0f;
  float etat = ior;

  if (cosi > 0) {
    std::swap(etai, etat);
  }

  // snell's law
  float sint = etai / etat * sqrtf(std::max(0.0f, 1.0f - cosi * cosi));

  // total internal reflection
  if (sint >= 1.0f) {
    return 1.0f;
  }
  else {

    float cost = sqrtf(std::max(0.0f, 1.0f - sint * sint)); 
    cosi = fabsf(cosi); 
    float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
    float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 

    return (Rs * Rs + Rp * Rp) / 2;

  }

}

// check if the given renderer instance is valid
bool Renderer::is_valid() {

  if (cam_ == nullptr) {
    std::cerr << "Renderer: Camera points to null in file '" << 
                 filename_ << "'." << std::endl;
    return false;
  }

  // test if defined filename has "ppm" ending
  std::regex REGEX_ppm ("^.+\\.ppm$");
  if (!std::regex_match(filename_, REGEX_ppm)) {
    std::cerr << "Renderer: Given file name '" << filename_ << 
                 "' has no '.ppm' file ending." << std::endl;
    return false;
  }

  return true;

}

void Renderer::render(int flags) {

  float width_f = static_cast<float>(width_);
  float height_f = static_cast<float>(height_);

  // go through all pixels
  for (unsigned y = 0; y < height_; y++) {
    for (unsigned x = 0; x < width_; x++) {

      // reset recursion limit for each new ray
      recursion_limit = initial_recursion_limit;

      // current pixel
      Pixel p(x, y);

      // anti-aliasing to smooth out sharp edges, or "jaggies"
      if (flags & ANTIALIASING) {
      
        // go through 4 sub pixels for this pixel
        for (float y_sub = 0.0f; y_sub < 1.0f; y_sub += 0.5f) {
          for (float x_sub = 0.0f; x_sub < 1.0f; x_sub += 0.5f) {

            recursion_limit = initial_recursion_limit;

            // send out ray for pixel position
            Ray eye_ray = cam_->compute_eye_ray(static_cast<float>(x + x_sub), static_cast<float>(y + y_sub));
            
            // assign color returned by ray
            p.color += 0.25f * trace(eye_ray);

          }
        }
      }
      // no anti aliasing
      else {

        // send out ray for pixel position
        Ray eye_ray = cam_->compute_eye_ray(static_cast<float>(x), static_cast<float>(y));
        
        // assign color returned by ray
        p.color  += trace(eye_ray);

      }

      write(p);

    }
  }

  // generate a string with the current date and time
  time_t _tm = time(NULL);
  struct tm * curtime = localtime ( &_tm );
  std::string time = asctime(curtime);
  std::replace(time.begin(), time.end(), ':', '-');

  // remove line break from 'time' (may be added in some operating systems)
  time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());

  // generate the full path (with name) and save the image
  full_path_ = output_directory_ + time + " " + filename_;
  std::cout << "Storing image at: " << full_path_ << std::endl;
  ppm_.save(full_path_);

}

// write current pixel into ppm file
void Renderer::write(Pixel const& p) {

  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) for pixel in .ppm ("
              << (int)p.x << ", " << (int)p.y << ")" << std::endl;
  } 
  else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);

}

Color Renderer::trace(Ray const& ray) {

  Color color;
  Color color_reflected;
  Color color_refracted;

  recursion_limit--;

  // check for intersections with all existing objects
  Hitpoint hp = find_intersection(ray);

  std::shared_ptr<Shape> hit_shape = nullptr;

  // find shape that has been hit by a ray
  hit_shape = root_->find_shape(hp.name_);

  if (hit_shape != nullptr) {

    std::shared_ptr<Material> material = hit_shape->get_material();

    static float attenuation = 1.0f;

    // material is a diffuse material
    if (material->refraction_index_ == 0.0f) {

      // iterate over all existing light sources
      for (auto const light : *lights_) {

        // test if it's a diffuse point light
        if (dynamic_cast<DiffusePointLight*>(light.get())) {

          // cast light pointer to DiffusePointLight pointer
          auto point_light_ptr = std::dynamic_pointer_cast<DiffusePointLight>(light);

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

          // test if there's no obstacle between light and object, then combine all colors
          if (!hp_light.has_hit_) {
            color += ambient + diffuse + specular;
          }
          // otherwise, the object is in shadow
          else {
            color += ambient;
          }

        }
        else if (dynamic_cast<AmbientLight*>(light.get())) {

          // cast light pointer to AmbientLight pointer
          auto ambient_light_ptr = std::dynamic_pointer_cast<AmbientLight>(light);

          // ambient
          static float ambient_intensity = ambient_light_ptr->intensity_;
          Color ambient = ambient_intensity * material->ka_ * ambient_light_ptr->color_;
          ambient *= attenuation;

          // only add ambient to final color
          color += ambient;

        }
      }

      // reflection for non-refractive diffuse object
      if (material->r_ > 0.0f && material->refraction_index_ == 0.0f) {

        if (recursion_limit > 0) {

          glm::vec3 reflection_direction = glm::normalize(glm::reflect(ray.direction_, hp.normal_));
          color_reflected = trace(Ray{hp.intersection_ + reflection_direction, reflection_direction});

          color += material->r_ * color_reflected;

        }
      }
    }
    // refraction
    else {

      if (recursion_limit > 0) {

        // with reflection
        if (material->r_ != 0.0f) {

          glm::vec3 reflection_direction = glm::normalize(glm::reflect(ray.direction_, hp.normal_));
          color_reflected = material->r_ * trace(Ray{hp.intersection_ + reflection_direction, reflection_direction});

        }

        float kr = fresnel(ray.direction_, hp.normal_, material->refraction_index_);

        bool outside = glm::dot(ray.direction_, hp.normal_) < 0.0f;

        // transparency
        if (material->transparency_ > 0.0f) {

          glm::vec3 refraction_direction = refract(ray.direction_, hp.normal_, material->refraction_index_);
          color_refracted = (1.0f - kr) * trace(Ray{hp.intersection_ + refraction_direction, refraction_direction});

        }

        color += color_reflected * material->transparency_ + color_refracted * material->transparency_;
      }
    }
  }
  // otherwise, return background color
  else {
    return background_;
  }

  // apply tone mapping to reduce high contrast
  tone_mapping(color);

  // perform gamma correction
  color = gamma_correction(color);

  return color;

}

// tone mapping reduces high contrast by shortening dynamic color range
void Renderer::tone_mapping(Color& color) {

  color.r = color.r / (color.r + 1);
  color.g = color.g / (color.g + 1);
  color.b = color.b / (color.b + 1);

}

// gamma correction counteracts false human perception of linear changes,
// for example black (darkness) to white (light)
Color Renderer::gamma_correction(Color& color) {

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