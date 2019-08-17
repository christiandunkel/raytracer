#include "composite.hpp"
#include <exception>

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

  std::cout << "Adding child: " << shape->get_name() << " to parent: " << get_name() << std::endl;
  children_.push_back(shape);
}

std::shared_ptr<Shape> hidden_search_holder = nullptr;

void recursive_iterate(std::string const& hit_name, std::shared_ptr<Shape> shape) {

  auto composite_ptr = std::static_pointer_cast<Composite>(shape);

  for (auto const child : composite_ptr->children_) {

    if (child->get_name() == hit_name) {
      hidden_search_holder = std::static_pointer_cast<Shape>(child);
    }
    else {
      recursive_iterate(hit_name, child);
    }
  }
}

std::shared_ptr<Shape> iterate(std::string const& hit_name, std::shared_ptr<Shape> shape) {

  recursive_iterate(hit_name, shape);

  return hidden_search_holder;
}