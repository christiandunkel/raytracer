#include "sdfManager.hpp"
#include "scene.hpp"
#include "renderer.hpp"
#include "window.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[]) {

  SdfManager manager;
  std::unique_ptr<Scene> scene = manager.parse("./resource/materials_test.sdf");
  //Renderer renderer;

  /*

  //create separate thread to see updates of pixels while rendering
  std::thread render_thread([&renderer]() {renderer.render();});

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.get_color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  render_thread.join();
  return 0;

  */

}
