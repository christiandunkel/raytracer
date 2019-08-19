#include "composite.hpp"

Composite::Composite(std::shared_ptr<Shape> shape) {

  add_child(shape);
}

void Composite::scale(glm::vec3 const& s) {

  for (auto const child : children_) {
    child->scale(s);
  }
}

void Composite::rotate(float angle, glm::vec3 const& axis) {

  for (auto const child : children_) {
    child->rotate(angle, axis);
  }
}

void Composite::translate(glm::vec3 const& t) {

  for (auto const child : children_) {
    child->translate(t);
  }
}

void Composite::add_child(std::shared_ptr<Shape> shape) {

  //std::cout << "Adding child: " << shape->get_name() << " to parent: " << get_name() << std::endl;
  children_.push_back(shape);
}