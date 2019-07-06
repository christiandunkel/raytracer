#ifndef SDFMANAGER_HPP
#define SDFMANAGER_HPP

#include "material.hpp"

#include <memory>
#include <vector>
#include <set>
#include <map>

class SdfManager {

  private:

    std::vector<std::shared_ptr<Material>> material_vec_;
    std::set<std::shared_ptr<Material>> material_set_;
    std::map<std::string, std::shared_ptr<Material>> material_map_;

    bool file_exists(std::string const& file_path);

  public:

    SdfManager() = default;

    void parse(std::string const& file_path);

    std::vector<std::shared_ptr<Material>> get_material_vec() const {
      return material_vec_;
    }

    std::set<std::shared_ptr<Material>> get_material_set() const {
      return material_set_;
    }

    std::map<std::string, std::shared_ptr<Material>> get_material_map() const {
      return material_map_;
    }

    std::shared_ptr<Material> find_material_in_vec(std::string const& name) const;
    std::shared_ptr<Material> find_material_in_set(std::string const& name) const;
    std::shared_ptr<Material> find_material_in_map(std::string const& name) const;

};

#endif // SDFMANAGER_HPP