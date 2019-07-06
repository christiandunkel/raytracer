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

    Box(glm::vec3 min, glm::vec3 max, std::shared_ptr<Material> material) :
      Shape(material), min_(min), max_(max) {
        std::cout << "Created box " + name_ << std::endl;
      }

    Box(glm::vec3 min, glm::vec3 max, std::shared_ptr<Material> material, std::string name) :
      Shape(name, material), min_(min), max_(max) {
        std::cout << "Created box " + name_ << std::endl;
      }
    
    ~Box() override;

    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream& os) const override;

    Hitpoint intersect(Ray const &ray, float distance) const override;

    // getter
    glm::vec3 get_min() const {return min_;}
    glm::vec3 get_max() const {return max_;}

};

#endif // define BOX_HPP