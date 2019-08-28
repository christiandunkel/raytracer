#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <memory>
#include "color.hpp"

struct Material {

  std::string name_ = "";

  // material coefficients
  Color ka_{1.0f, 1.0f, 1.0f}; // ambient
  Color kd_{1.0f, 1.0f, 1.0f}; // diffuse
  Color ks_{1.0f, 1.0f, 1.0f}; // specular

  // specular reflections exponent
  float m_ = 0.0f;

  // reflection coefficient
  float r_ = 0.0f; 

  float refraction_index_;

  // transparency coeffiecient
  float transparency_;

  std::ostream& print(std::ostream& os) const;

};

void print_material(const std::shared_ptr<Material> material);

#endif // MATERIAL_HPP