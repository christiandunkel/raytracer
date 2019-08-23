#include <iostream>
#include <string.h>

int main(int argc, char* argv[]) {

  // use default generation values
  if (argc == 3 && strcmp(argv[1], "--file") == 0) {

  }
  else {
    std::cerr << "Use '--file \"./../../resource/simple_scene.sdf\"' to load a scene" << std::endl;
    return -1;
  }

  

  return 0;
}