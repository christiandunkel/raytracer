#include "material.hpp"

std::ostream& Material::print(std::ostream& os) const {

  std::string ambient_color = "[" + 
    std::to_string(this->ka_.r) + ", " + 
    std::to_string(this->ka_.g) + ", " + 
    std::to_string(this->ka_.b) + 
  "]";

  std::string diffuse_color = "[" + 
    std::to_string(this->kd_.r) + ", " + 
    std::to_string(this->kd_.g) + ", " + 
    std::to_string(this->kd_.b) + 
  "]";

  std::string specular_color = "[" + 
    std::to_string(this->ks_.r) + ", " + 
    std::to_string(this->ks_.g) + ", " + 
    std::to_string(this->ks_.b) +
  "]";

  os << "Material:" << std::endl <<
        "\tName: " << this->name_ << std::endl <<
        "\tAmbient Color: " << ambient_color << std::endl <<
        "\tDiffuse Color: " << diffuse_color << std::endl <<
        "\tSpecular Color: " << specular_color << std::endl <<
        "\tSpecular Reflections Exponent: " << this->m_ << std::endl;

  return os;

}

void print_material(const std::shared_ptr<Material> material) {

  std::cout << material;

}