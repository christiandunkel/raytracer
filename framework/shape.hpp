#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>

#include "color.hpp"

class Shape {

  protected:

    std::string name_;
    Color color_;

    Shape() :
      name_("default"), color_(Color(1.0f, 1.0f, 1.0f)) {}

    Shape(std::string name) :
      name_(name), color_(Color(1.0f, 1.0f, 1.0f)) {}

    Shape(Color color) :
      name_("default"), color_(color) {}

    Shape(std::string name, Color color) :
      name_(name), color_(color) {}
  
    virtual float area() const = 0;
    virtual float volume() const = 0;
 
};

#endif // define SHAPE_HPP