#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "camera.hpp"
#include <string>
#include <memory>
#include <glm/glm.hpp>

class Renderer {

  private:

    PpmWriter ppm_;
    std::shared_ptr<Camera> cam_;

    std::string filename_;
    std::vector<Color> color_buffer_;

    unsigned int width_;
    unsigned int height_;

  public:

    Renderer() = default;

    Renderer(std::string const& file, std::shared_ptr<Camera> cam, unsigned int w, unsigned int h) : 
      ppm_(w, h), cam_(cam), filename_(file), color_buffer_(w * h, Color{0.0, 0.0, 0.0}), width_(w), height_(h) {}

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

};

#endif // RENDERER_HPP
