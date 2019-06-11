#include "box.hpp"

float Box::area() const {
  // area = 2*l*w + 2*l*h + 2*w*h
  float side_x = max_.x - min_.x,
        side_y = max_.y - min_.y,
        side_z = max_.z - min_.z;
  return 2 * (side_x * side_y + 
              side_y * side_z + 
              side_x * side_z);
}

float Box::volume() const {
  // volume = length * width * height
  float side_x = max_.x - min_.x,
        side_y = max_.y - min_.y,
        side_z = max_.z - min_.z;
  return side_x * side_y * side_z;
}

// print box object
std::ostream& Box::print(std::ostream& os) const {
  os << "{\"sphere\":{\n" <<
            "   name: " << name_ << ",\n" <<
            "   min: {" << 
                    min_.x << "," <<
                    min_.y << "," <<
                    min_.z << 
            "},\n" << 
            "   max: {" << 
                    max_.x << "," <<
                    max_.y << "," <<
                    max_.z << 
            "},\n" << 
            "   color: " << color_ <<
        "}}";
  return os;
}