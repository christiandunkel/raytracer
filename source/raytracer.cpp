#include "sdfManager.hpp"
#include "scene.hpp"
#include "renderer.hpp"
#include "window.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[]) {

  // load scene from sdf file
  SdfManager manager;
  std::unique_ptr<Scene> scene = manager.parse("./resource/simple_scene.sdf");

  // get first renderer
  int renderer_index = 0;
  Renderer* renderer = &scene->renderer_vec_.at(renderer_index);

  int renderer_num = scene->renderer_vec_.size();

  // set root element in renderer
  renderer->root_ = std::static_pointer_cast<Composite>(scene->root_);

  // set camera
  renderer->cam_ = scene->camera_map_.begin()->second;

  renderer->render();

  Window window{{renderer->get_width(), renderer->get_height()}};

  bool wait_after_event = false;

  unsigned int counter = 0;

  while (!window.should_close()) {

    // to avoid input spamming
    counter++;

    if (counter % 50 == 0) {
      wait_after_event = false;

      // reset counter to avoid overflow
      counter = 0;
    }

    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      renderer->is_running = false;
      window.close();
    }
    else if (window.get_key(GLFW_KEY_SPACE) == GLFW_PRESS && !wait_after_event) {

      wait_after_event = true;

      if  (renderer_index >= renderer_num - 1) {
        // last renderer reached, close
        window.close();
      }
      else {
        renderer_index++;
        renderer = &scene->renderer_vec_.at(renderer_index);

        // do changes here (e.g. apply further transformations)

        renderer->render();
      }
    }

    window.show(renderer->get_color_buffer());

  }

  return 0;

}
