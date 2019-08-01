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
    bool is_number(const std::string& s);

    void parse_material(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values);
    void parse_shape(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values);
    void parse_light(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values);
    void parse_camera(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values);
    void parse_render(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values);

};

#endif // SDFMANAGER_HPP