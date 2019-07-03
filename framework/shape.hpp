#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>

#include "color.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"

class Shape {

  protected:

    std::string name_;
    Color color_;

    Shape() :
      name_("default"), color_(Color(1.0f, 1.0f, 1.0f)) {
        std::cout << "Created shape " + name_ << std::endl;
      }

    Shape(std::string name) :
      name_(name), color_(Color(1.0f, 1.0f, 1.0f)) {
        std::cout << "Created shape " + name_ << std::endl;
      }

    Shape(Color color) :
      name_("default"), color_(color) {
        std::cout << "Created shape " + name_ << std::endl;
      }

    Shape(std::string name, Color color) :
      name_(name), color_(color) {
        std::cout << "Created shape " + name_ << std::endl;
      }
  
    virtual float area() const = 0;
    virtual float volume() const = 0;

    virtual Hitpoint intersect(Ray const &ray, float distance) const = 0;

  public:

    virtual std::ostream& print(std::ostream& os) const;
    virtual ~Shape();
 
};

std::ostream& operator <<(std::ostream& os, Shape const& s);

#endif // define SHAPE_HPP