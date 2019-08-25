#include "animation.hpp"
#include <iostream>
#include <sstream>

void Animation::set_axis(std::string const& axis) {

  if (axis == "X") {
    axis_ = X;
  }
  else if (axis == "Y") {
    axis_ = Y;
  }
  else if (axis == "Z") {
    axis_ = Z;
  }
  else if (axis == "XY" || "YX") {
    axis_ = XY;
  }
  else if (axis == "XZ" || "ZX") {
    axis_ = XZ;
  }
  else if (axis == "XYZ" || "XZY" || "YXZ" || "YZX" || "ZXY" || "ZYX") {
    axis_ = XYZ;
  }
  else {
    std::cerr << "Animation: Axis not supported" << std::endl;
  }
}

void Animation::set_frames(std::string const& start_frame, std::string const& end_frame) {

  unsigned int frame;

  std::istringstream start_str(start_frame);
  start_str >> frame;
  start_frame_ = frame;

  std::istringstream end_str(end_frame);
  end_str >> frame;
  end_frame_ = frame;
}

std::string Animation::get_transform() {

  tick_++;

  std::string transform = "define transform ";

  if (shape_ != nullptr) {

    transform += shape_->get_name() + " ";

    switch (type_) {

      case SCALE:
        transform += "scale " + get_scale();

        break;

      case ROTATE:
        transform += "rotate " + get_rotation();

        break;

      case TRANSLATE:
        transform += "translate " + get_translation();

        break;
    }
  }
  else {
    std::cerr << "Animation: No shape has been defined." << std::endl;
  }

  return transform;
}

std::string Animation::get_scale() {

  std::string scale;



  return scale;
}

std::string Animation::get_rotation() {

  float angle = speed_ * tick_;

  std::string rotation = std::to_string(angle) + " ";

  switch (axis_) {
    case X:
      rotation += "1 0 0";
      break;
    case Y:
      rotation += "0 1 0";
      break;
    case Z:
      rotation += "0 0 1";
      break;
    case XY:
      rotation += "1 1 0";
      break;
    case XZ:
      rotation += "1 0 1";
      break;
    case YZ:
      rotation += "0 1 1";
      break;
    case XYZ:
      rotation += "1 1 1";
      break;
  }

  return rotation;
}

std::string Animation::get_translation() {

  std::string translation;


  return translation;
}
