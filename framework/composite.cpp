#include "composite.hpp"

std::shared_ptr<Shape> hidden_search_holder = nullptr;

Composite::Composite(std::shared_ptr<Shape> shape) {

  add_child(shape);
}

void Composite::find_intersection(Hitpoint& first_hit, Ray const& ray) const {

  for (auto const child : children_) {
    child->find_intersection(first_hit, ray);
  }
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

std::shared_ptr<Shape> Composite::find_shape(std::string const& name) const {

  hidden_search_holder = nullptr;

  // convert composite raw pointer to shared pointer of shape
  std::shared_ptr<Shape> root = std::make_shared<Composite>(*this);

  find_shape_recursively(root, name);

  return hidden_search_holder;
}

void find_shape_recursively(std::shared_ptr<Shape> root, std::string const& name) {

  if (root->get_name() == name) {
    hidden_search_holder = root;
  }
  else {

    if (dynamic_cast<Composite*>(root.get())) {

      auto composite_ptr = std::static_pointer_cast<Composite>(root);

      for (auto child : composite_ptr->children_) {

        find_shape_recursively(child, name);
      }
    }
  }
}