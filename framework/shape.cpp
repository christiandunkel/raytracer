#include "shape.hpp"

#define GLM_EXPERIMENTAL_ENABLED
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

void Shape::scale(glm::vec3 const& s) {

  world_transform_ = glm::scale(world_transform_, s);

  // update the inverse of world transform matrix
  world_transform_inv_ = glm::inverse(world_transform_);
}

void Shape::rotate(float angle, glm::vec3 const& axis) {

  world_transform_ = glm::rotate(world_transform_, glm::radians(angle), axis);

  // update the inverse of world transform matrix
  world_transform_inv_ = glm::inverse(world_transform_);
}

void Shape::translate(glm::vec3 const& t) {

  world_transform_ = glm::translate(world_transform_, t);

  // update the inverse of world transform matrix
  world_transform_inv_ = glm::inverse(world_transform_);
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