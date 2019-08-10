#ifndef SCENE_HPP
#define SCENE_HPP

#include "shape.hpp"
#include "material.hpp"
#include "light.hpp"
#include "camera.hpp"

#include <memory>
#include <vector>
#include <set>
#include <map>

class Scene {

  public:

    std::vector<std::shared_ptr<Shape>> shape_vec_;
    std::vector<std::shared_ptr<Light>> light_vec_;
    std::map<std::string, std::shared_ptr<Camera>> camera_map_;
    std::map<std::string, std::shared_ptr<Material>> material_map_;

    Scene() = default;

    std::shared_ptr<Shape> find_shape(std::string const& name) const;
    std::shared_ptr<Light> find_light(std::string const& name) const;
    std::shared_ptr<Camera> find_camera(std::string const& name) const;
    std::shared_ptr<Material> find_material(std::string const& name) const;
};

#endif // SDFMANAGER_HPP