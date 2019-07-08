#include "sdfManager.hpp"

#include <regex>
#include <sys/stat.h>
#include <fstream>
#include <ctype.h>

bool is_number(const std::string& s) {

  std::string::const_iterator it = s.begin();

  while (it != s.end() && std::isdigit(*it)) {
    ++it;
  }

  return !s.empty() && it == s.end();
}

SdfManager::SdfManager(std::string const& file_path) {
  parse(file_path);
}

std::unique_ptr<Scene> SdfManager::parse(std::string const& file_path) {

  if (!file_exists(file_path)) {
    std::cout << "File " << file_path << " wasn't found." << std::endl;
    return nullptr;
  }

  std::ifstream file(file_path);

  if (file.is_open()) {

    std::unique_ptr<Scene> res = std::make_unique<Scene>();

    std::string line;
    while (getline(file, line)) {

      std::regex REGEX_define ("^define .*");

      // only use lines beginning with "define"
      if (!std::regex_match(line, REGEX_define)) {
        continue;
      }

      // split string into words / values
      std::istringstream iss(line);
      std::vector<std::string> parts{std::istream_iterator<std::string>(iss),
                                     std::istream_iterator<std::string>()};

      if (parts.size() < 3) {
        continue;
      }

      if (parts.at(1) == "material") {

        // remove "define material"
        parts.erase(parts.begin()); // removes "define"
        parts.erase(parts.begin()); // removes "material"

        // material must have 11 (name, 3 colors, one float) values
        if (parts.size() != 11) {
          continue;
        }

        for (size_t i = 0; i < parts.size(); i++) {
          if (is_number(parts.at(i))) {
            continue;
          }
        }

        std::cout << "SDFManager: Found material '" + parts.at(0) + "' in " << file_path << "." << std::endl;

        std::shared_ptr<Material> material = std::make_shared<Material>();

        material->name_ = parts.at(0);

        material->ka_ = {stof(parts.at(1)), stof(parts.at(2)), stof(parts.at(3))};
        material->kd_ = {stof(parts.at(4)), stof(parts.at(5)), stof(parts.at(6))};
        material->ks_ = {stof(parts.at(7)), stof(parts.at(8)), stof(parts.at(9))};

        material->m_ = stof(parts.at(10));

        res->material_vec_.push_back(material);
        res->material_set_.emplace(material);
        res->material_map_.emplace(std::make_pair(material->name_, material));
      }



    }
    file.close();

    return res;
  }
  else {
    std::cout << "File " << file_path << " couldn't be opened." << std::endl;
  }

  return nullptr;
}

bool SdfManager::file_exists(std::string const& file_path) {
  struct stat buffer;
  return (stat (file_path.c_str(), &buffer) == 0);
}
