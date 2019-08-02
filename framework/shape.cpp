#include "shape.hpp"

Shape::~Shape() {
  std::cout << "Destroyed shape " + name_ << std::endl;
}

// print shape object
std::ostream& Shape::print(std::ostream& os) const {
  
  os << "Shape:" << std::endl <<
        "\tName: " << name_ << std::endl;
        material_->print(os);
  
  return os;
}

std::ostream& operator <<(std::ostream& os, Shape const& s) {
  return s.print(os);
}

void Shape::set_name(std::string const& name) {
  name_ = name;
}

void Shape::set_material(std::shared_ptr<Material> material) {
  material_ = material; 
}