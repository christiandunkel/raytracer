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

void print_help_menu(std::string const example_path) {

    std::cout << "--file \"path_to_file\"\n"
      << "\tTakes a path to an existing sdf file and renders the image using it.\n"
      << "\tUse path '" << example_path << "' for a predefined scene." << std::endl;

    std::cout << "--frames \"n\"\n"
      << "\tCreates n images.\n"
      << "\tRequires a sdf file that defines at least one animation." << std::endl;

    std::cout << "--aa\n"
      << "\tEnables anti-aliasing using 4 sub pixels." << std::endl;

    std::cout << "--recursion \"n\"\n"
      << "\tSets the recursion depths of ray relfection and refraction." << std::endl;

}

int main(int argc, char* argv[]) {

  // load scene from sdf file
  SdfManager manager;
  std::unique_ptr<Scene> scene = nullptr;

  bool is_animated = false;
  std::string output_directory = "./../../output/";
  std::string example_path = "./input/simpleScene.sdf";

  int flags = 0;
  int file_pos = -1;
  int frames_pos = -1;
  int aa_pos = -1;
  int recursion_pos = -1;

  // command line parsing
  for (unsigned int i = 1; i < argc; i++) {

    if (strcmp(argv[i], "--file") == 0 && i < argc) {
      file_pos = i + 1;
      flags |= SOURCE;
      i++;
    }
    else if (strcmp(argv[i], "--frames") == 0 && i < argc) {
      frames_pos = i + 1;
      flags |= FRAMES;
      i++;
    }
    else if (strcmp(argv[i], "--aa") == 0) {
      aa_pos = i;
      flags |= ANTIALIASING;
    }
    else if (strcmp(argv[i], "--recursion") == 0 && i < argc) {
      recursion_pos = i + 1;
      flags |= RECURSION;
      i++;
    }
    else if (strcmp(argv[i], "--help") == 0) {
      flags |= HELP;
      break;
    }
    else {
      flags = 0;
      std::cerr << "Unknown command line parameters\n"
        << "Use '--help'" << std::endl;

      return -1;
    }
  }

  // print help instructions
  if (flags >= 16) {
    print_help_menu(example_path);
    return 0;
  }
  // default start up
  else if (flags < 8) {

    scene = manager.parse(example_path);

    output_directory = "output/";

  }
  // start up with file path
  else if (flags & SOURCE) {

    // parse file at given path
    scene = manager.parse(argv[file_pos]);

  }

  if (scene == nullptr) {
    std::cerr << "Scene file couldn't be parsed. Use '--help'" << std::endl;
    return -1;
  }

  // generate animation if so set in terminal parameter (flags)
  if (flags & FRAMES) {
    manager.generate_files(argv[file_pos], argv[frames_pos], scene.get());
    is_animated = true;
  }

  // get first renderer and set image output directory
  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(scene->renderer_);
  renderer->output_directory_ = output_directory;

  // set recursion depth
  if (flags & RECURSION) {
    renderer->initial_recursion_limit = atoi(argv[recursion_pos]);
  }

  // set up renderer with flags
  renderer->render(flags);

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

      scene = manager.parse(updated_path);

      if (scene == nullptr) {
        std::cout << animation_index << " images have been generated." << std::endl;
        return 0;
      }

      renderer = std::make_unique<Renderer>(scene->renderer_);

      // set image output directory
      renderer->output_directory_ = output_directory;

      // set recursion depth
      if (flags & RECURSION) {
        renderer->initial_recursion_limit = atoi(argv[recursion_pos]);
      }

      renderer->render(flags);

      animation_index++;

    }

    // close window on ESC press
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }

    // display new frame
    window.show(renderer->get_color_buffer());

  }

  return 0;

}