#ifndef SDFMANAGER_HPP
#define SDFMANAGER_HPP

#include "material.hpp"

#include <memory>
#include <vector>
#include <set>
#include <map>

class SdfManager {

  public:

    std::vector<std::shared_ptr<Material>> material_vec_;
    std::set<std::shared_ptr<Material>> material_set_;
    std::map<std::string, std::shared_ptr<Material>> material_map_;

    SdfManager() = default;

    bool file_exists(std::string const& file_path);

    void parse(std::string const& file_path);

    std::shared_ptr<Material> find_material_in_vec(std::string const& name) const;
    std::shared_ptr<Material> find_material_in_set(std::string const& name) const;
    std::shared_ptr<Material> find_material_in_map(std::string const& name) const;

};

#endif // SDFMANAGER_HPP