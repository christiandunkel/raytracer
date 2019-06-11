#include "shape.hpp"

// print shape object
std::ostream& Shape::print(std::ostream& os) const {
  os << "{\"shape\":{\n" <<
            "   name: " << name_ << ",\n" << 
            "   color: " << color_ << 
        "}}";
  return os;
}

std::ostream& operator <<(std::ostream& os, Shape const& s) {
  return s.print(os);
}