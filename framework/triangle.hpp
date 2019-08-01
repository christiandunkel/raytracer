#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape {

  private:

    glm::vec3 a_;
    glm::vec3 b_;
    glm::vec3 c_;

  public:

    Triangle() :
      a_(glm::vec3(0.0f)), b_(glm::vec3(0.0f)), c_(glm::vec3(0.0f)) {
        std::cout << "Created triangle " << name_ << std::endl;
      }

    Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) :
      a_(a), b_(b), c_(c) {
        std::cout << "Created triangle " << name_ << std::endl;
      }

    Triangle(std::string name, std::shared_ptr<Material> material, glm::vec3 a, glm::vec3 b, glm::vec3 c) :
      Shape(name, material), a_(a), b_(b), c_(c) {
        std::cout << "Created triangle " << name_ << std::endl;
      }

    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream& os) const override;

    Hitpoint intersect(Ray const &ray, float distance) const override;

    glm::vec3 get_a() const {return a_;}
    glm::vec3 get_b() const {return b_;}
    glm::vec3 get_c() const {return c_;}

};


#endif // TRIANGLE_HPP