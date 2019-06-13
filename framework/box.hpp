#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>

#include "color.hpp"
#include "shape.hpp"

class Box : public virtual Shape {

  private:
  
    glm::vec3 min_;
    glm::vec3 max_;

  public:

    Box() :
      min_(glm::vec3(0.0f, 0.0f, 0.0f)), max_(glm::vec3(0.0f, 0.0f, 0.0f)) {
        std::cout << "Created box " + name_ << std::endl;
      }

    Box(std::string name) :
      Shape(name), min_(glm::vec3(0.0f, 0.0f, 0.0f)), max_(glm::vec3(0.0f, 0.0f, 0.0f)) {
        std::cout << "Created box " + name_ << std::endl;
      }

    Box(glm::vec3 min, glm::vec3 max) :
      min_(min), max_(max) {
        std::cout << "Created box " + name_ << std::endl;
      }

    Box(glm::vec3 min, glm::vec3 max, Color color) :
      Shape(color), min_(min), max_(max) {
        std::cout << "Created box " + name_ << std::endl;
      }

    Box(glm::vec3 min, glm::vec3 max, Color color, std::string name) :
      Shape(name, color), min_(min), max_(max) {
        std::cout << "Created box " + name_ << std::endl;
      }
    
    ~Box() override;

    virtual float area() const override;
    virtual float volume() const override;
    std::ostream& Box::print(std::ostream& os) const override;

    // getter
    glm::vec3 get_min() const {return min_;}
    glm::vec3 get_max() const {return max_;}
    Color get_color() const {return color_;}
    std::string get_name() const {return name_;}
 
};

#endif // define BOX_HPP