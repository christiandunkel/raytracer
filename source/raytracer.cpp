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

  //create separate thread to see updates of pixels while rendering
  //std::thread render_thread([&renderer]() {renderer->render();});
  renderer->render();

  Window window{{renderer->get_width(), renderer->get_height()}};

  while (!window.should_close()) {

    //renderer->render();

    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      renderer->is_running = false;
      window.close();
    }
    else if (window.get_key(GLFW_KEY_SPACE) == GLFW_PRESS) {

      if  (renderer_index >= renderer_num) {
        // last renderer reached, close
        window.close();
      }
      else {
        renderer_index++;
        renderer = &scene->renderer_vec_.at(renderer_index);
      }

    }

    window.handle_events();

    window.show(renderer->get_color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  //render_thread.join();

  return 0;

}
