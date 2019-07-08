#ifndef SDFMANAGER_HPP
#define SDFMANAGER_HPP

#include "material.hpp"
#include "scene.hpp"

class SdfManager {

  public:

    SdfManager() = default;
    SdfManager(std::string const& file_path);

    std::unique_ptr<Scene> parse(std::string const& file_path);

  private:

    bool file_exists(std::string const& file_path);

};

#endif // SDFMANAGER_HPP