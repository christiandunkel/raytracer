#include "scene.hpp"

#include <algorithm>

// returns a shape of scene found by name
std::shared_ptr<Shape> Scene::find_shape(std::string const& name) const {

  for (auto it : shape_vec_) {

    if (it->get_name() == name) {
      return it;
    }
  }

  return nullptr;
}

// returns a light of scene found by name
std::shared_ptr<Light> Scene::find_light(std::string const& name) const {

  for (auto it : light_vec_) {

    if (it->name_ == name) {
      return it;
    }
  }

  return nullptr;
}

// returns a camera of scene found by name
std::shared_ptr<Camera> Scene::find_camera(std::string const& name) const {

  auto it = camera_map_.find(name);

  if (it->second != nullptr) {
    return it->second;
  }

  return nullptr;

}

// returns a material of scene found by name
std::shared_ptr<Material> Scene::find_material(std::string const& name) const {

  auto it = material_map_.find(name);

  if (it->second != nullptr) {
    return it->second;
  }

  return nullptr;
}
