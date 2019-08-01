#include "sdfManager.hpp"
#include "box.hpp"
#include "sphere.hpp"

#include <regex>
#include <sys/stat.h>
#include <fstream>
#include <ctype.h>

// on construction of object, parse given sdf file
SdfManager::SdfManager(std::string const& file_path) {
  parse(file_path);
}

// test if file exists at given path
bool SdfManager::file_exists(std::string const& file_path) {
  struct stat buffer;
  return (stat (file_path.c_str(), &buffer) == 0);
}

// test if given string can be converted to a number
bool SdfManager::is_number(const std::string& s) {

  std::string::const_iterator it = s.begin();

  while (it != s.end() && std::isdigit(*it)) {
    ++it;
  }

  return !s.empty() && it == s.end();

}

// parse sdf file, convert data to objects and return scene
std::unique_ptr<Scene> SdfManager::parse(std::string const& file_path) {

  // look up file at path, check if it exists
  if (!file_exists(file_path)) {
    std::cout << "SdfManager: File '" << file_path << "' wasn't found." << std::endl;
    return nullptr;
  }

  // read file
  std::ifstream file(file_path);

  if (file.is_open()) {

    // generate scene object to return
    std::unique_ptr<Scene> scene = std::make_unique<Scene>();

    // read line for line
    std::string line;
    while (getline(file, line)) {

      // only use lines starting with "define"
      std::regex REGEX_define ("^define .*");
      if (!std::regex_match(line, REGEX_define)) {
        continue;
      }

      // split string into words and values (by space)
      std::istringstream iss(line);
      std::vector<std::string> parts{std::istream_iterator<std::string>(iss),
                                     std::istream_iterator<std::string>()};

      // check if there are at least 3 parts to string
      if (parts.size() < 3) {
        continue;
      }

      // remove "define" from beginning of string
      parts.erase(parts.begin());

      if (parts.at(0) == "material") {
        parse_material(file_path, scene, parts);
      }
      else if (parts.at(0) == "shape") {
        parse_shape(file_path, scene, parts);
      }
      else if (parts.at(0) == "light") {
        parse_light(file_path, scene, parts);
      }
      else if (parts.at(0) == "camera") {
        parse_camera(file_path, scene, parts);
      }
      else if (parts.at(0) == "render") {
        parse_render(file_path, scene, parts);
      }
      else {
        std::cout << "SdfManager: Given type '" << parts.at(0) << "' doesn't exist." << std::endl;
      }

    }
    file.close();

    return scene;

  }
  else {
    std::cout << "SdfManager: File '" << file_path << "' couldn't be opened." << std::endl;
  }

  return nullptr;
}

void SdfManager::parse_material(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "material" from beginning of string
  values.erase(values.begin());

  // material must have 11 (name, 3 colors (3x3=9), one float) values
  if (values.size() != 11) {
    return;
  }

  // test if all values after name are numbers
  for (size_t i = 1; i < values.size(); i++) {
    if (!is_number(values.at(i))) {
      return;  
    }
  }

  std::cout << "SdfManager: Found material '" + values.at(0) + "' in " << file_path << "." << std::endl;

  // create new material and fill it with values
  std::shared_ptr<Material> material = std::make_shared<Material>();
  material->name_ = values.at(0);
  material->ka_ = {stof(values.at(1)), stof(values.at(2)), stof(values.at(3))};
  material->kd_ = {stof(values.at(4)), stof(values.at(5)), stof(values.at(6))};
  material->ks_ = {stof(values.at(7)), stof(values.at(8)), stof(values.at(9))};
  material->m_ = stof(values.at(10));

  // push material into containers
  scene->material_vec_.push_back(material);
  scene->material_set_.emplace(material);
  scene->material_map_.emplace(std::make_pair(material->name_, material));

}

void SdfManager::parse_shape(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "shape" from beginning of string
  values.erase(values.begin());

  std::shared_ptr<Shape> shape;

  if (values.at(0) == "box") {

    shape = std::make_shared<Box>();

  }
  else if (values.at(0) == "sphere") {



  }
  else if (values.at(0) == "triangle") {

  }
  else {
    std::cout << "SdfManager: Shape type '" + values.at(0) + "' in " << file_path << " doesn't exist." << std::endl;
  }

}

void SdfManager::parse_light(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

}

void SdfManager::parse_camera(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

}

void SdfManager::parse_render(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

}