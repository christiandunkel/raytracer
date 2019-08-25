#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "shape.hpp"

#include <glm/vec3.hpp>
#include <string>
#include <memory>

enum TransformationType {
  SCALE, TRANSLATE, ROTATE
};

enum Axis {
  X, Y, Z, XY, XZ, YZ, XYZ,
};

class Animation {

  public:

    std::shared_ptr<Shape> shape_;

    TransformationType type_;
    Axis axis_;

    unsigned int end_frame_;
    unsigned int start_frame_;
    unsigned int tick_ = 0;

    float speed_;

    Animation() = default;

    void set_axis(std::string const& axis);
    void set_frames(std::string const& start_frame, std::string const& end_frame);

    std::string get_transform();

  private:

    std::string get_scale();
    std::string get_rotation();
    std::string get_translation();
};

#endif // ANIMATION_HPP