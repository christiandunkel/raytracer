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

    glm::mat4 world_transform_;
    glm::mat4 world_transform_inv_;

    Shape() :
      name_("default"), world_transform_(glm::mat4(1.0f)), world_transform_inv_(glm::inverse(world_transform_)) {
        //std::cout << "Created shape " + name_ << std::endl;
        material_ = std::make_shared<Material>();
      }

    Shape(std::string name) :
      name_(name), world_transform_(glm::mat4(1.0f)), world_transform_inv_(glm::inverse(world_transform_)) {
        //std::cout << "Created shape " + name_ << std::endl;
        material_ = std::make_shared<Material>();
      }

    Shape(std::shared_ptr<Material> material) :
      name_("default"), material_(material), world_transform_(glm::mat4(1.0f)), world_transform_inv_(glm::inverse(world_transform_)) {
        //std::cout << "Created shape " + name_ << std::endl;
      }

    Shape(std::string name, std::shared_ptr<Material> material) :
      name_(name), material_(material), world_transform_(glm::mat4(1.0f)), world_transform_inv_(glm::inverse(world_transform_)) {
        //std::cout << "Created shape " + name_ << std::endl;
      }

    virtual float area() const = 0;
    virtual float volume() const = 0;

  public:

    virtual std::ostream& print(std::ostream& os) const;
    virtual ~Shape();

    virtual Hitpoint intersect(Ray const &ray, float distance = 0.0f) const = 0;
    virtual void find_intersection(Hitpoint& first_hit, Ray const& ray) const;

    virtual void scale(glm::vec3 const& s);
    virtual void rotate(float angle, glm::vec3 const& axis);
    virtual void translate(glm::vec3 const& t);

    virtual std::shared_ptr<Shape> find_shape(std::string const& name) const {}

    std::string get_name() const {
      return name_;
    }

    std::shared_ptr<Material> get_material() const {
      return material_;
    }

    void set_name(std::string const& name);
    void set_material(std::shared_ptr<Material> material); 

};

std::ostream& operator <<(std::ostream& os, Shape const& s);

#endif // define SHAPE_HPP