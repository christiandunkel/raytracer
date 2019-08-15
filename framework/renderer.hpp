#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "window.hpp"
#include "ppmwriter.hpp"
#include "camera.hpp"
#include "shape.hpp"
#include "light.hpp"

#include <string>
#include <memory>
#include <glm/glm.hpp>

class Renderer {

  public:

    bool is_running;
    std::shared_ptr<Camera> cam_;
    std::shared_ptr<std::vector<std::shared_ptr<Shape>>> shapes_;
    std::shared_ptr<std::vector<std::shared_ptr<Light>>> lights_;
    std::vector<Color> color_buffer_;

  private:

    PpmWriter ppm_;

    std::string filename_;

    unsigned int width_;
    unsigned int height_;

  public:

    Renderer() = default;

    Renderer(std::string const& file, std::shared_ptr<Camera> cam, unsigned int w, unsigned int h) : 
      is_running(true), ppm_(w, h), cam_(cam), filename_(file), color_buffer_(w * h, Color{0.0, 0.0, 0.0}), width_(w), height_(h) {}

    bool is_valid();
    void render();
    void write(Pixel const& p);

    inline std::vector<Color> const& get_color_buffer() const {
      return color_buffer_;
    }

    inline std::string const get_filename() const {
      return filename_;
    }

    inline unsigned int const get_width() const {
      return width_;
    }

    inline unsigned int const get_height() const {
      return height_;
    }

  private:

    Color trace(Ray const& ray);
    //Color shade(std::shared_ptr<Shape> shape, Hitpoint const& hitpoint, float distance);

    Color calc_ambient_color(Hitpoint const& hitpoint, std::shared_ptr<Shape> shape);
    Color calc_diffuse_color(Hitpoint const& hitpoint, std::shared_ptr<Shape> shape);
    Color calc_specular_color(Hitpoint const& hitpoint, std::shared_ptr<Shape> shape);
};

#endif // RENDERER_HPP
