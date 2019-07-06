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

void SdfManager::parse(std::string const& file_path) {

  if (!file_exists(file_path)) {
    std::cout << "File " << file_path << " wasn't found." << std::endl;
    return;
  }

  std::ifstream file(file_path);

  if (file.is_open()) {
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
        parts.erase(parts.begin());
        parts.erase(parts.begin() + 1);

        // material must have 11 (name, 3 colors, one float) values
        if (parts.size() != 11) {
          continue;
        }

        for (size_t i = 0; i < parts.size(); i++) {
          if (is_number(parts.at(i))) {
            continue;
          }
        }

        std::cout << "SDFManager: Found material in " << file_path << "." << std::endl;

        std::shared_ptr<Material> material = std::make_shared<Material>();

        material->name_ = parts.at(0);

        material->ka_ = {stof(parts.at(1)), stof(parts.at(2)), stof(parts.at(3))};
        material->kd_ = {stof(parts.at(4)), stof(parts.at(5)), stof(parts.at(6))};
        material->ks_ = {stof(parts.at(7)), stof(parts.at(8)), stof(parts.at(9))};

        material->m_ = stof(parts.at(10));

        material_vec_.push_back(material);
        material_set_.emplace(material);
        material_map_.emplace(std::make_pair(material->name_, material));
      }



    }
    file.close();
  }
  else {
    std::cout << "File " << file_path << " couldn't be opened." << std::endl;
  }

}

bool SdfManager::file_exists(std::string const& file_path) {
  struct stat buffer;
  return (stat (file_path.c_str(), &buffer) == 0);
}

std::shared_ptr<Material> SdfManager::find_material_in_vec(std::string const& name) const {

  for (auto it : material_vec_) {

    if (it->name_ == name) {
      return it;
    }
  }

  return nullptr;
}

std::shared_ptr<Material> SdfManager::find_material_in_set(std::string const& name) const {

  auto it = find_if(material_set_.begin(), material_set_.end(), [&](std::shared_ptr<Material> m) {
    return m->name_ == name;
  });

  if (*it != nullptr) {
    return *it;
  }

  return nullptr;
}

std::shared_ptr<Material> SdfManager::find_material_in_map(std::string const& name) const {



  return nullptr;
}
