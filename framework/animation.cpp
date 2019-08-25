#include "animation.hpp"
#include <iostream>
#include <sstream>

void Animation::set_axis(std::string const& axis) {

  if (axis == "X" || axis == "x") {
    axis_ = X;
  }
  else if (axis == "Y" || axis == "y") {
    axis_ = Y;
  }
  else if (axis == "Z" || axis == "z") {
    axis_ = Z;
  }
  else if (axis == "XY" || axis == "xy") {
    axis_ = XY;
  }
  else if (axis == "XZ" || axis == "xz") {
    axis_ = XZ;
  }
  else if (axis == "XYZ" || axis == "xyz") {
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

  std::string factor = std::to_string(speed_ * tick_);

  switch (axis_) {
    case X:
      scale += factor + " 0 0";
      break;
    case Y:
      scale += "0 " + factor + " 0";
      break;
    case Z:
      scale += "0 0 " + factor;
      break;
    case XY:
      scale += factor + " " + factor + " 0";
      break;
    case XZ:
      scale += factor + " 0 " + factor;
      break;
    case YZ:
      scale += "0 " + factor + " " + factor;
      break;
    case XYZ:
      scale += factor + " " + factor + " " + factor;
      break;
  }

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

  return get_scale();
}