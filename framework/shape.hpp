#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>

#include "color.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include "material.hpp"

class Shape {

  protected:

    std::string name_;
    std::shared_ptr<Material> material_;

    Shape() :
      name_("default") {
        std::cout << "Created shape " + name_ << std::endl;
        material_ = std::make_shared<Material>();
      }

    Shape(std::string name) :
      name_(name) {
        std::cout << "Created shape " + name_ << std::endl;
        material_ = std::make_shared<Material>();
      }

    Shape(std::shared_ptr<Material> material) :
      name_("default"), material_(material) {
        std::cout << "Created shape " + name_ << std::endl;
      }

    Shape(std::string name, std::shared_ptr<Material> material) :
      name_(name), material_(material) {
        std::cout << "Created shape " + name_ << std::endl;
      }
  
    virtual float area() const = 0;
    virtual float volume() const = 0;

    virtual Hitpoint intersect(Ray const &ray, float distance) const = 0;

  public:

    virtual std::ostream& print(std::ostream& os) const;
    virtual ~Shape();

    std::string get_name() const {
      return name_;
    }

    std::shared_ptr<Material> get_material() const {
      return material_;
    }
 
};

std::ostream& operator <<(std::ostream& os, Shape const& s);

#endif // define SHAPE_HPP