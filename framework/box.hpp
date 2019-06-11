#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>

#include "color.hpp"
#include "shape.hpp"

class Box : public Shape {

  private:
  
    glm::vec3 min_;
    glm::vec3 max_;

  public:

    Box() :
      Shape(), min_(glm::vec3(0.0f, 0.0f, 0.0f)), max_(glm::vec3(0.0f, 0.0f, 0.0f)) {}

    Box(std::string name) :
      Shape(name), min_(glm::vec3(0.0f, 0.0f, 0.0f)), max_(glm::vec3(0.0f, 0.0f, 0.0f)) {}

    Box(glm::vec3 min, glm::vec3 max) :
      Shape(), min_(min), max_(max) {}

    Box(Color color, glm::vec3 min, glm::vec3 max) :
      Shape(color), min_(min), max_(max) {}

    Box(std::string name, Color color, glm::vec3 min, glm::vec3 max) :
      Shape(name, color), min_(min), max_(max) {}

    virtual float area() const override;
    virtual float volume() const override;
    std::ostream& Box::print(std::ostream& os) const override;

    // getter
    std::string get_name() const {return name_;}
    Color get_color() const {return color_;}
    glm::vec3 get_min() const {return min_;}
    glm::vec3 get_max() const {return max_;}
 
};

#endif // define BOX_HPP