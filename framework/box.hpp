#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>

#include "shape.hpp"

class Box : public Shape {

  private:

    glm::vec3 min_;
    glm::vec3 max_;

  public:

    Box() :
      min_(glm::vec3(0.0f, 0.0f, 0.0f)), max_(glm::vec3(0.0f, 0.0f, 0.0f)) {}

    Box(glm::vec3 min, glm::vec3 max) :
      min_(min), max_(max) {}

    virtual float area() const override;
    virtual float volume() const override;

    glm::vec3 get_min() {return min_;}
    glm::vec3 get_max() {return max_;}
 
};

#endif // define BOX_HPP