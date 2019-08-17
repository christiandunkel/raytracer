#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "shape.hpp"
#include <vector>
#include <memory>

// scene graph for the poor kids
class Composite : public Shape {

  public:

    std::vector<std::shared_ptr<Shape>> children_;

    Composite() = default;
    Composite(std::shared_ptr<Shape> shape);

    float area() const override {return 0.0f;}
    float volume() const override {return 0.0f;}

    Hitpoint intersect(Ray const& ray, float distance) const override {return Hitpoint{};}

    void scale(glm::vec3 const& s) override;
    void rotate(float angle, glm::vec3 const& axis) override;
    void translate(glm::vec3 const& t) override;

    void add_child(std::shared_ptr<Shape> shape);
};

std::shared_ptr<Shape> iterate(std::string const& hit_name, std::shared_ptr<Shape> shape);

#endif // COMPOSITE_HPP