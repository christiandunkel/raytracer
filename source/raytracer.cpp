#include "sdfManager.hpp"
#include "scene.hpp"
#include "renderer.hpp"
#include "window.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

  // load scene from sdf file
  SdfManager manager;
  std::unique_ptr<Scene> scene = nullptr;

  bool is_animated = false;
  std::string output_directory = "./../../output/";

  // command line parsing
  if (argc == 1) {

    std::cout << "Parsing scene at: ./resource/simple_scene.sdf" << std::endl;
    scene = manager.parse("./resource/simple_scene.sdf");
    output_directory = "output/";
  }
  else if (argc == 3 && strcmp(argv[1], "--file") == 0) {

    std::cout << "Parsing scene at: " << argv[2] << std::endl;
    scene = manager.parse(argv[2]);
  }
  else if (argc == 4 && strcmp(argv[1], "--file") == 0 && strcmp(argv[3], "--animated") == 0) {

    std::cout << "Parsing scene at: " << argv[2] << std::endl;
    scene = manager.parse(argv[2]);
    is_animated = true; 
  }

  if (scene == nullptr) {
    std::cerr << "Use '--file \"./../../resource/simple_scene.sdf\"' to load a scene" << std::endl;
    std::cerr << "use '--animated' to generate multiple images" << std::endl;
    return -1;
  }

  /*
  TODO:
    put renderer->render() in separate thread to keep window responsive and show rendering progress
  */

  // get first renderer
  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(scene->renderer_);

  // set root element in renderer
  renderer->root_ = scene->root_;

  // set camera
  renderer->cam_ = scene->camera_map_.begin()->second;

  // set image output  directory
  renderer->output_directory_ = output_directory;

  renderer->render();

  std::cout << "Storing image at: " << renderer->full_path_ << std::endl;

  Window window{{renderer->get_width(), renderer->get_height()}};

  bool first_iteration = true;

  unsigned int animation_index = 1;

  while (!window.should_close()) {

    // use already set up renderer in first frame
    if (first_iteration) {
      first_iteration = false;
    }
    // update renderer to use next scene only if animation is enabled
    else if (!first_iteration && is_animated) {

      static std::string path = argv[2];

      size_t pos_underscore = path.find("_");
      size_t pos_file_ending = path.find(".sdf");

      // replace number after underscore in file name with the next number to generate a new image
      std::string updated_path =  path.substr(0, pos_underscore + 1) + std::to_string(animation_index) + path.substr(pos_file_ending);

      std::cout << "Parsing scene at: " << updated_path << std::endl;

      scene = manager.parse(updated_path);

      if (scene == nullptr) {
        std::cout << animation_index << " images have been generated." << std::endl;
        return -1;
      }

      renderer = std::make_unique<Renderer>(scene->renderer_);

      renderer->output_directory_ = output_directory;

      // set next root element
      renderer->root_ = scene->root_;

      // set next camera
      renderer->cam_ = scene->camera_map_.begin()->second;

      renderer->render();

      std::cout << "Storing image at: " << renderer->full_path_ << std::endl;

      animation_index++;
    }

    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }

    window.show(renderer->get_color_buffer());    
  }

  return 0;

}
