#include "shape.hpp"

Shape::~Shape() {
  std::cout << "Destroyed shape " + name_ << std::endl;
}

// print shape object
std::ostream& Shape::print(std::ostream& os) const {
  os << "{\"shape\":{\n" <<
            "   name: " << name_ << ",\n" << 
            "   color: " << color_ << 
        "}}" << std::endl;
  return os;
}

std::ostream& operator <<(std::ostream& os, Shape const& s) {
  return s.print(os);
}