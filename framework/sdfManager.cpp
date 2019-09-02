#include "sdfManager.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "composite.hpp"

#include <regex>
#include <sys/stat.h>
#include <fstream>
#include <ctype.h>
#include <cctype>
#include <sstream>

// test if file exists at given path
bool SdfManager::file_exists(std::string const& file_path) {
  struct stat buffer;
  return (stat (file_path.c_str(), &buffer) == 0);
}

// test if given string can be converted to a number
bool SdfManager::is_number(std::string const& s) {

  std::istringstream iss(s);
  float f;
  iss >> std::noskipws >> f;

  return iss.eof() && !iss.fail();

}

// parse sdf file, convert data to objects and return pointer to scene
std::unique_ptr<Scene> SdfManager::parse(std::string const& file_path) {

  std::cout << "Parsing scene defined in file " << file_path << "." << std::endl;

  // look up file at path, check if it exists
  if (!file_exists(file_path)) {
    std::cerr << "SdfManager: File '" << file_path << 
                 "' wasn't found." << std::endl;
    return nullptr;
  }

  // read file
  std::ifstream file(file_path);

  if (file.is_open()) {

    // generate scene object to return
    std::unique_ptr<Scene> scene = std::make_unique<Scene>();

    // read line for line
    std::string line;
    while (std::getline(file, line)) {
      
      // only use lines starting with "define" or "render"
      std::regex REGEX_valid ("^(define|render) .*");
      if (!std::regex_match(line, REGEX_valid)) {
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

      // detect type of command in current line of sdf file
      if (parts.at(0) == "define") {

        // remove "define" from beginning of string
        parts.erase(parts.begin());

        if (parts.at(0) == "material") {
          parse_material(file_path, scene, parts);
        }
        else if (parts.at(0) == "background") {
          parse_background(file_path, scene, parts);
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
        else if (parts.at(0) == "transform") {
          parse_transform(file_path, scene, parts);
        }
        else if (parts.at(0) == "animation") {

          // make sure that animation tags get only parsed in the initial file
          static bool first_line_with_animation = true;

          if (first_line_with_animation) {
            parse_animation(file_path, scene, parts);
            first_line_with_animation = false;
          }

        }
        else {
          std::cerr << "SdfManager: Given definition '" << parts.at(0) << 
                       "' used in file " << file_path << 
                       " is not valid." << std::endl;
        }

      }
      else if (parts.at(0) == "render") {
        parse_render(file_path, scene, parts);
      }

    }
    file.close();

    return scene;

  }
  else {
    std::cerr << "SdfManager: File at path '" << file_path << 
                 "' couldn't be opened." << std::endl;
  }

  return nullptr;
}

// parse material definition in sdf file
void SdfManager::parse_material(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "material" from beginning of string
  values.erase(values.begin());

  // material must have 14 (name, 3 colors (3x3=9), 4 floats) values
  if (values.size() != 14) {
    std::cerr << "SdfManager: A material '" << values.at(0) << 
                 "' defined in file '" << file_path << 
                 "' couldn't be opened." << std::endl;
    return;
  }

  // test if all values after name are numbers
  for (size_t i = 1; i < values.size(); i++) {
    if (!is_number(values.at(i))) {
      return;
    }
  }

  // create new material and fill it with values
  std::shared_ptr<Material> material = std::make_shared<Material>();
  material->name_ = values.at(0);
  material->ka_ = {stof(values.at(1)), stof(values.at(2)), stof(values.at(3))};
  material->kd_ = {stof(values.at(4)), stof(values.at(5)), stof(values.at(6))};
  material->ks_ = {stof(values.at(7)), stof(values.at(8)), stof(values.at(9))};
  material->m_ = stof(values.at(10));
  material->r_ = stof(values.at(11));
  material->refraction_index_ = stof(values.at(12));
  material->transparency_ = stof(values.at(13));

  // push material into containers
  scene->material_map_.emplace(std::make_pair(material->name_, material));

}

// parse background definition in sdf file
void SdfManager::parse_background(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "background" from beginning of string
  values.erase(values.begin());

  if (values.size() == 3) {
    scene->background_ = Color {stof(values.at(0)), stof(values.at(1)), stof(values.at(2))};
  }
}

// parse shape definition in sdf file
void SdfManager::parse_shape(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "shape" from beginning of string
  values.erase(values.begin());

  std::shared_ptr<Shape> shape;

  if (values.at(0) == "box") {

    shape = std::make_shared<Box>();
    shape->set_name(values.at(1));

    std::shared_ptr<Box> box_ptr = std::dynamic_pointer_cast<Box>(shape);
    box_ptr->set_min(glm::vec3(stof(values.at(2)), stof(values.at(3)), stof(values.at(4))));
    box_ptr->set_max(glm::vec3(stof(values.at(5)), stof(values.at(6)), stof(values.at(7))));
    box_ptr->set_material(scene->find_material(values.at(8)));

  }
  else if (values.at(0) == "sphere") {

    shape = std::make_shared<Sphere>();
    shape->set_name(values.at(1));

    std::shared_ptr<Sphere> sphere_ptr = std::dynamic_pointer_cast<Sphere>(shape);
    sphere_ptr->set_middle(glm::vec3(stof(values.at(2)), stof(values.at(3)), stof(values.at(4))));
    sphere_ptr->set_radius(stof(values.at(5)));
    sphere_ptr->set_material(scene->find_material(values.at(6)));

  }
  else if (values.at(0) == "triangle") {

    shape = std::make_shared<Triangle>();
    shape->set_name(values.at(1));

    std::shared_ptr<Triangle> triangle_ptr = std::dynamic_pointer_cast<Triangle>(shape);
    triangle_ptr->set_a(glm::vec3(stof(values.at(2)), stof(values.at(3)), stof(values.at(4))));
    triangle_ptr->set_b(glm::vec3(stof(values.at(5)), stof(values.at(6)), stof(values.at(7))));
    triangle_ptr->set_c(glm::vec3(stof(values.at(8)), stof(values.at(9)), stof(values.at(10))));

    triangle_ptr->set_material(scene->find_material(values.at(11)));

  }
  else if (values.at(0) == "composite") {

    // return if composite has no children
    if (values.size() <= 2) {
      return;
    }

    shape = std::make_shared<Composite>();
    shape->set_name(values.at(1));

    std::shared_ptr<Composite> composite_ptr = std::dynamic_pointer_cast<Composite>(shape);

    for (size_t i = 2; i < values.size(); i++) {

      std::shared_ptr<Shape> temp = scene->find_shape(values.at(i));

      if (temp != nullptr) {
        composite_ptr->add_child(temp);
      }
      else {
        std::cerr << "SdfManager: Shape '" << values.at(i) << 
                    "' defined in file " << file_path << 
                    " and used by composite '" << composite_ptr->get_name() <<
                    "' doesn't exist." << std::endl;
      }
    }

    // last composite always has to be the root element
    scene->root_ = shape;

  }
  else {
    std::cerr << "SdfManager: Shape type '" << values.at(0) << 
                 "' defined in file " << file_path << 
                 " doesn't exist." << std::endl;
    return;
  }

  scene->shape_vec_.push_back(shape);

}

// parse light definition in sdf file
void SdfManager::parse_light(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "light" from beginning of string
  values.erase(values.begin());

  std::shared_ptr<Light> light;

  // check if a diffuse point light was defined
  if (values.size() == 8) {

    light = std::make_shared<DiffusePointLight>();
    light->name_ = values.at(0);

    std::shared_ptr<DiffusePointLight> point_light_ptr = std::dynamic_pointer_cast<DiffusePointLight>(light);
    point_light_ptr->pos_ = glm::vec3(stof(values.at(1)), stof(values.at(2)), stof(values.at(3)));
    point_light_ptr->color_ = Color(stof(values.at(4)), stof(values.at(5)), stof(values.at(6)));
    point_light_ptr->intensity_ = stof(values.at(7));
  }
  // otherwise, it might be an ambient light
  else if (values.size() == 5) {

    light = std::make_shared<AmbientLight>();
    light->name_ = values.at(0);

    std::shared_ptr<AmbientLight> point_light_ptr = std::dynamic_pointer_cast<AmbientLight>(light);
    point_light_ptr->color_ = Color(stof(values.at(1)), stof(values.at(2)), stof(values.at(3)));
    point_light_ptr->intensity_ = stof(values.at(4));

  }
  // else, the light type can't be determined
  else {
    std::cerr << "SdfManager: Light type '" << values.at(0) << 
                 "' defined in file " << file_path << 
                 " doesn't exist." << std::endl;
    return;
  }

  // add light to container
  scene->light_vec_.push_back(light);

}

// parse camera definition in sdf file
void SdfManager::parse_camera(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "camera" from beginning of string
  values.erase(values.begin());

  // camera with all parameters
  if (values.size() == 11) {

    glm::vec3 pos = glm::vec3(stof(values.at(2)), stof(values.at(3)), stof(values.at(4)));
    glm::vec3 front = glm::vec3(stof(values.at(5)), stof(values.at(6)), stof(values.at(7)));
    glm::vec3 world_up = glm::vec3(stof(values.at(8)), stof(values.at(9)), stof(values.at(10)));

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(values.at(0), stof(values.at(1)), pos, front, world_up);

    scene->camera_map_.emplace(std::make_pair(camera->name_, camera));

  }
  else {
    std::cerr << "SdfManager: Camera '" << values.at(0) << 
                 "' defined in file " << file_path << 
                 " couldn't be parsed." << std::endl;
  }

}

// parse render definition in sdf file
void SdfManager::parse_render(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "render" from beginning of string
  values.erase(values.begin());

  // find camera
  std::shared_ptr<Camera> cam = scene->find_camera(values.at(0));

  if (cam == nullptr) {
    std::cerr << "SdfManager: Renderer with camera '" << values.at(0) << 
                 "' defined in file " << file_path << 
                 " doesn't exist (yet)." << std::endl;
    return;
  }

  if (values.size() == 4) {

    std::istringstream width_str(values.at(2));
    unsigned int width;
    width_str >> width;

    std::istringstream height_str(values.at(3));
    unsigned int height;
    height_str >> height;

    cam->set_screen_dimensions(width, height);

    Renderer renderer{values.at(1), cam, width, height};

    renderer.lights_ = std::make_shared<std::vector<std::shared_ptr<Light>>>(scene->light_vec_);
    renderer.root_ = scene->root_;
    renderer.background_ = scene->background_;
    renderer.cam_ = scene->camera_map_.begin()->second;

    scene->renderer_ = renderer;

  }
  else {
    std::cerr << "SdfManager: Renderer '" << values.at(0) << 
                 "' defined in file " << file_path << 
                 " can't be parsed." << std::endl;
  }

}

// parse transform definition in sdf file
void SdfManager::parse_transform(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "transform" from beginning of string
  values.erase(values.begin());

  std::shared_ptr<Shape> shape = scene->find_shape(values.at(0));

  if (shape != nullptr) {

    if (values.at(1) == "scale" && values.size() == 5) {
      shape->scale(glm::vec3(stof(values.at(2)), stof(values.at(3)), stof(values.at(4))));
    }
    else if (values.at(1) == "rotate" && values.size() == 6) {
      shape->rotate(stof(values.at(2)), glm::vec3(stof(values.at(3)), stof(values.at(4)), stof(values.at(5))));
    }
    else if (values.at(1) == "translate" && values.size() == 5) {
      shape->translate(glm::vec3(stof(values.at(2)), stof(values.at(3)), stof(values.at(4))));
    }
    else {
      std::cerr << "SdfManager: Transform type '" << values.at(0) << 
                   "' defined in file " << file_path << 
                   " is not valid." << std::endl;
    }
    
  }
  else {
    std::cerr << "SdfManager: Shape '" << values.at(0) << 
                 "' used by transform in file " << file_path << 
                 " doesn't exist (yet)." << std::endl;
  }

}

// parse animation definition in sdf file
void SdfManager::parse_animation(std::string const& file_path, std::unique_ptr<Scene>& scene, std::vector<std::string>& values) {

  // remove "animation" from beginning of string
  values.erase(values.begin());

  std::shared_ptr<Shape> shape = scene->find_shape(values.at(0));

  if (shape != nullptr) {

    if (values.size() >= 4) {

      Animation animation;

      if (values.at(1) == "scale") {
        animation.type_ = SCALE;
      }
      else if (values.at(1) == "rotate") {
        animation.type_ = ROTATE;
      }
      else if (values.at(1) == "translate") {
        animation.type_ = TRANSLATE;
      }
      else {
        std::cerr << "SdfManager: Transform type '" << values.at(1) << 
                     "' for animation used in " << file_path << 
                     " does not exist." << std::endl;
        return;
      }

      animation.shape_ = shape;
      animation.set_axis(values.at(2));
      animation.speed_ = stof(values.at(3));

      if (values.size() == 4) {
        animation.start_frame_ = 0;
        animation.end_frame_ = std::numeric_limits<unsigned int>::max();
      }
      else if (values.size() == 5) {
        animation.set_frames(values.at(4), "0");
        animation.end_frame_ = std::numeric_limits<unsigned int>::max();
      }
      else {
        animation.set_frames(values.at(4), values.at(5));
      }
      scene->animation_vec_.push_back(animation);
    }
    else {
      std::cerr << "SdfManager: Animation in " << file_path << 
                   "couldn't be parsed." << std::endl;
    }

  }
  else {
    std::cerr << "SdfManager: Shape '" << values.at(0) << 
                 "' used by animation in " << file_path << 
                 " doesn't exist (yet)." << std::endl;
  }

}

// generate sdf files for an animated scene
void SdfManager::generate_files(std::string const& file_path, std::string const& frames, Scene* scene) {

  static std::string path = file_path;

  size_t pos_underscore = path.find("_");
  size_t pos_file_ending = path.find(".sdf");

  // convert string to uint 'limit'
  std::istringstream frame_str(frames);
  unsigned int limit;
  frame_str >> limit;

  std::string updated_path;

  for (unsigned int i = 1; i < limit; i++) {

    // replace number after underscore in file name with the next number to generate a new sdf file
    updated_path = path.substr(0, pos_underscore + 1) + std::to_string(i) + path.substr(pos_file_ending);

    // copy files
    std::ifstream src(file_path, std::ios::binary);
    std::ofstream dst(updated_path, std::ios::binary);

    dst << src.rdbuf();

    for (auto &animation : scene->animation_vec_) {

      if (i >= animation.start_frame_ && i < animation.end_frame_) {

        // retrieve new transform line and add to file
        std::string transform = "\n" + animation.get_transform();
        dst << transform;

      }
    }
  }

  std::cout << "SdfManager: Generated " << limit << " SDF files." << std::endl;

}