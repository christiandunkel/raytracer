#include "composite.hpp"

std::shared_ptr<Shape> hidden_search_holder = nullptr;

void Composite::find_intersection(Hitpoint& first_hit, Ray const& ray) const {
  for (auto const child : children_) {
    child->find_intersection(first_hit, ray);
  }
}

// scale all children in composite
void Composite::scale(glm::vec3 const& s) {
  for (auto const child : children_) {
    child->scale(s);
  }
}

// rotate all children in composite
void Composite::rotate(float angle, glm::vec3 const& axis) {
  for (auto const child : children_) {
    child->rotate(angle, axis);
  }
}

// translate all children in composite
void Composite::translate(glm::vec3 const& t) {
  for (auto const child : children_) {
    child->translate(t);
  }
}

// add child given as parameter to composite
void Composite::add_child(std::shared_ptr<Shape> shape) {
  children_.push_back(shape);
}

// find shape by name in composite 
std::shared_ptr<Shape> Composite::find_shape(std::string const& name) const {

  hidden_search_holder = nullptr;

  // convert composite raw pointer to shared pointer of shape
  std::shared_ptr<Shape> root = std::make_shared<Composite>(*this);

  find_shape_recursively(root, name);

  return hidden_search_holder;

}

// find shape by name in composite recursively
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