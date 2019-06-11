// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Window
// -----------------------------------------------------------------------------

#include "window.hpp"
#include <utility>
#include <cstring>
#include <iostream>
#include <cassert>
#include <exception>

const char* v_sh_source = R"(
#version 330
out vec2 vertex_texture_coordinates;
void main()
{
  vertex_texture_coordinates = vec2(float(gl_VertexID / 2) * 2.0, float(gl_VertexID % 2) * 2.0);
  gl_Position = vec4((float(gl_VertexID / 2) * 4.0) - 1.0,
                     (float(gl_VertexID % 2) * 4.0) - 1.0,
                     0.0,
                     1.0);
}
)";

const char* f_sh_source = R"(
#version 330
uniform sampler2D image;
in vec2 vertex_texture_coordinates;

out vec4 FragColor;

void main()
{
  vec4 color = texture(image, vertex_texture_coordinates).rgba;
  FragColor = color;
}
)";

namespace {
void errorcb(int error, const char* desc)
{
  std::cerr << "GLFW error " << error << ": " << desc << std::endl;
}
}

Window::Window(glm::ivec2 const& window_size)
  : window_{nullptr}
  , window_size_(window_size)
  , frame_buffer_size_{window_size}
  , title_("Raytracer")
{
  if (!glfwInit()) {
    throw "Could not init glfw";
  }
  glfwSetErrorCallback(errorcb);
  //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

  glfwWindowHint(GLFW_RESIZABLE, 0);

  window_ = glfwCreateWindow(window_size_.x, window_size_.y, title_.c_str(), nullptr, nullptr);
  if (!window_) {
    glfwTerminate();
    throw "Could not create window";
  }

  glfwMakeContextCurrent(window_);

  //  the pollable state of a mouse button will remain GLFW_PRESS until the
  //  state of that button is polled with glfwGetMouseButton. Once it has been
  //  polled, if a mouse button release event had been processed in the
  //  meantime, the state will reset to GLFW_RELEASE, otherwise it will remain
  //  GLFW_PRESS.
  glfwSetInputMode(window_, GLFW_STICKY_MOUSE_BUTTONS, 1);

  glfwSetWindowUserPointer(window_, this);
  assert(window_ != nullptr);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
      throw "Could not init glew";
  }
  glGetError();

  // Begin Frame
  glfwGetFramebufferSize(window_, &frame_buffer_size_.x, &frame_buffer_size_.y);

  // Calculate pixel ration for hi-dpi devices.
  float pxRatio = float(frame_buffer_size_.x) / float(window_size_.x);
  glViewport(0, 0, frame_buffer_size_.x, frame_buffer_size_.y);
  glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  //nvgBeginFrame(m_nvgContext, window_Size.x, window_Size.y, pxRatio);
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &v_sh_source ,0);
  glCompileShader(vertex_shader);
  GLint result = GL_FALSE;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
  if (result != GL_TRUE) {
    std::string log(1000, '*');
    glGetShaderInfoLog(vertex_shader, 1000, 0, (GLchar*)log.data());
    std::cout << "Error vertex shader: " << log;
    throw "Error glCompileShader vertex";
  }
  auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &f_sh_source ,0);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
  if (result != GL_TRUE) {
    std::string log(1000, '*');
    glGetShaderInfoLog(fragment_shader, 1000, 0, (GLchar*)log.data());
    std::cout << "Error fragment shader: " << log;
    throw "Error glCompileShader fragment";
  }
  program_ = glCreateProgram();
  glAttachShader(program_, vertex_shader);
  glAttachShader(program_, fragment_shader);
  glLinkProgram(program_);
  glUseProgram(program_);
  GLint image_loc = glGetUniformLocation(program_, "image");
  if (image_loc != -1) {
    glUniform1i(image_loc, 0);
  }
  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, window_size_.x, window_size_.y);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Window::~Window()
{
  glDeleteVertexArrays(1, &vao_);
  glfwTerminate();
}

int Window::get_key(int key) const
{
  return glfwGetKey(window_, key);
}

int Window::get_mouse_button(int button) const
{
  return glfwGetMouseButton(window_, button);
}

bool Window::should_close() const
{
  return glfwWindowShouldClose(window_);
}

glm::vec2 Window::mouse_position() const
{
  double xpos=0.0;
  double ypos=0.0f;
  glfwGetCursorPos(window_, &xpos, &ypos);
  return glm::vec2(float(xpos), float(ypos));
}

void Window::close()
{
  glfwSetWindowShouldClose(window_, GL_TRUE);
}

void Window::update()
{
  // End Frame
  glfwSwapBuffers(window_);
  glfwPollEvents();

  // Begin Frame
  glViewport(0, 0, frame_buffer_size_.x, frame_buffer_size_.y);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // Calculate pixel ration for hi-dpi devices.
  float pxRatio = float(frame_buffer_size_.x) / float(window_size_.x);
}

glm::ivec2 Window::window_size() const
{
  glm::ivec2 size(0);
  glfwGetFramebufferSize(window_, &size.x, &size.y);
  return size;
}

float Window::get_time() const
{
  return float(glfwGetTime());
}

void Window::show(std::vector<Color> const& color_buffer)
{
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, window_size_.x, window_size_.y, GL_RGB, GL_FLOAT, color_buffer.data());
  glBindVertexArray(vao_);
  glUseProgram(program_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);
  update();
}
