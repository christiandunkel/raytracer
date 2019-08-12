#include "renderer.hpp"
#include "camera.hpp"

#include "sphere.hpp"

#include <regex>

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

  for (unsigned y = 0; y < height_; y++) {
    for (unsigned x = 0; x < width_; x++) {

      Pixel p(x, y);

      Ray eye_ray = cam_->compute_eye_ray(x, y, height_, width_);

      p.color = color_buffer_.at(x*y);
      p.color = trace(eye_ray);

      write(p);

    }
  }

  // generate a sub folder with date & time as name
  time_t _tm =time(NULL );
  struct tm * curtime = localtime ( &_tm );
  std::string time = asctime(curtime);
  std::replace(time.begin(), time.end(), ':', '-');

  ppm_.save("output/" + time + " " + filename_);

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

void Renderer::set_camera(std::shared_ptr<Camera> camera) {
  cam_ = camera;
}

void Renderer::set_shapes(std::vector<std::shared_ptr<Shape>> const& shapes) {
  shapes_ = shapes;
}

Color Renderer::trace(Ray const& ray) {

  float closest_d = 0.0f;
  std::shared_ptr<Shape> closest_s = nullptr;

  for (std::shared_ptr<Shape> const& shape : shapes_) {

    Hitpoint hp = shape->intersect(ray, closest_d);

    if (hp.distance_ > closest_d) {
      closest_d = hp.distance_;
      closest_s = shape;
    }
  }

  if (closest_s != nullptr) {
    return shade(closest_s, ray, closest_d);
  }

  return Color(0.1f, 0.1f, 0.1f);
}

Color Renderer::shade(std::shared_ptr<Shape> shape, Ray const& ray, float distance) {

  std::shared_ptr<Material> material = shape->get_material();

  return material->ka_ + material->kd_ + material->ks_; 
}