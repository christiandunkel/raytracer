// Window (C) Andreas-C. Bernstein

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "color.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <array>
#include <string>

struct GLFWwindow;

class Window {

  private:
  
    GLFWwindow*       window_;
    glm::ivec2        window_size_;
    glm::ivec2        frame_buffer_size_;
    std::string const title_;
    GLuint            vao_     = 0;
    GLuint            program_ = 0;
    GLuint            texture_ = 0;

  public:

    Window(glm::ivec2 const& window_size = {640, 480});
    ~Window();

    enum MouseButton {
      MOUSE_BUTTON_NONE   = 0,
      MOUSE_BUTTON_LEFT   = (1 << 0),
      MOUSE_BUTTON_RIGHT  = (1 << 1),
      MOUSE_BUTTON_MIDDLE = (1 << 2)
    };

    enum KeyAction {
      KEY_PRESS   = GLFW_PRESS,
      KEY_RELEASE = GLFW_RELEASE,
      KEY_REPEAT  = GLFW_REPEAT
    };

    glm::vec2 mouse_position() const;

    // is closed flag set
    bool should_close() const;

    // close window
    void close();

    // update window
    void update();

    // test if given key is pressed 
    // (key codes: http://www.glfw.org/docs/latest/group__keys.html)
    int get_key(int key) const;
    bool key_pressed(int key) const;
    int get_mouse_button(int button) const;

    // current window size
    glm::ivec2 window_size() const;

    // time elapsed since GLFW was initialized
    float get_time() const;

    void show(std::vector<Color> const& color_buffer);

};

#endif // WINDOW_HPP
