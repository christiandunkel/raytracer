#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include "sphere.hpp"
#include "box.hpp"
#include "ray.hpp"

int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}

TEST_CASE("Task 5.2", "Sphere, Box methods area(), volume()") {

  // sphere
  Sphere s1;
  REQUIRE(s1.get_radius() == Approx(0.0f).epsilon(0.001));
  REQUIRE(s1.get_middle() == glm::vec3(0.0f, 0.0f, 0.0f));
  REQUIRE(s1.area() == Approx(0.0f).epsilon(0.001));
  REQUIRE(s1.volume() == Approx(0.0f).epsilon(0.001));

  Sphere s2(glm::vec3(0.5f, 0.3f, 5.0f), 25.0f);
  REQUIRE(s2.get_radius() == Approx(25.0f).epsilon(0.001));
  REQUIRE(s2.get_middle() == glm::vec3(0.5f, 0.3f, 5.0f));
  REQUIRE(s2.area() == Approx(7853.98f).epsilon(0.001));
  REQUIRE(s2.volume() == Approx(65449.846f).epsilon(0.001));

  Sphere s3(-5.0f);
  REQUIRE(s3.get_radius() == Approx(-5.0f).epsilon(0.001));
  REQUIRE(s3.get_middle() == glm::vec3(0.0f, 0.0f, 0.0f));
  REQUIRE(s3.area() == Approx(-1.0f).epsilon(0.001)); // error -> returns -1f
  REQUIRE(s3.volume() == Approx(-1.0f).epsilon(0.001)); // error -> returns -1f

  // box
  Box b1;
  REQUIRE(b1.get_min() == glm::vec3(0.0f, 0.0f, 0.0f));
  REQUIRE(b1.get_max() == glm::vec3(0.0f, 0.0f, 0.0f));
  REQUIRE(b1.area() == Approx(0.0f).epsilon(0.001));
  REQUIRE(b1.volume() == Approx(0.0f).epsilon(0.001));

  Box b2(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
  REQUIRE(b2.get_min() == glm::vec3(1.0f, 1.0f, 1.0f));
  REQUIRE(b2.get_max() == glm::vec3(2.0f, 2.0f, 2.0f));
  REQUIRE(b2.area() == Approx(6.0f).epsilon(0.001));
  REQUIRE(b2.volume() == Approx(1.0f).epsilon(0.001));

}

TEST_CASE("Task 5.3", "name_, color_ attributes") {

  // sphere
  Sphere s1;
  REQUIRE(s1.get_name() == "default");
  REQUIRE(s1.get_color().r == Approx(1.0f).epsilon(0.001));
  REQUIRE(s1.get_color().g == Approx(1.0f).epsilon(0.001));
  REQUIRE(s1.get_color().b == Approx(1.0f).epsilon(0.001));

  Sphere s2(Color(0.3f, 0.4f, 0.5f), glm::vec3(0.5f, 0.3f, 5.0f), 25.0f);
  REQUIRE(s2.get_name() == "default");
  REQUIRE(s2.get_color().r == Approx(0.3f).epsilon(0.001));
  REQUIRE(s2.get_color().g == Approx(0.4f).epsilon(0.001));
  REQUIRE(s2.get_color().b == Approx(0.5f).epsilon(0.001));

  Sphere s3("test", Color(0.3f, 0.4f, 0.5f), glm::vec3(0.5f, 0.3f, 5.0f), 25.0f);
  REQUIRE(s3.get_name() == "test");
  REQUIRE(s3.get_color().r == Approx(0.3f).epsilon(0.001));
  REQUIRE(s3.get_color().g == Approx(0.4f).epsilon(0.001));
  REQUIRE(s3.get_color().b == Approx(0.5f).epsilon(0.001));

  // box
  Box b1;
  REQUIRE(b1.get_name() == "default");
  REQUIRE(b1.get_color().r == Approx(1.0f).epsilon(0.001));
  REQUIRE(b1.get_color().g == Approx(1.0f).epsilon(0.001));
  REQUIRE(b1.get_color().b == Approx(1.0f).epsilon(0.001));

  Box b2(Color(0.3f, 0.4f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  REQUIRE(b2.get_name() == "default");
  REQUIRE(b2.get_color().r == Approx(0.3f).epsilon(0.001));
  REQUIRE(b2.get_color().g == Approx(0.4f).epsilon(0.001));
  REQUIRE(b2.get_color().b == Approx(0.5f).epsilon(0.001));

  Box b3("test", Color(0.3f, 0.4f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  REQUIRE(b3.get_name() == "test");
  REQUIRE(b3.get_color().r == Approx(0.3f).epsilon(0.001));
  REQUIRE(b3.get_color().g == Approx(0.4f).epsilon(0.001));
  REQUIRE(b3.get_color().b == Approx(0.5f).epsilon(0.001));

}

TEST_CASE("Task 5.5", "Sphere, Box method print()") {

  // sphere
  std::cout << Sphere() << std::endl;

  // box
  std::cout << Box("test name") << std::endl;

}

// test for task 5.6 given in assignemnt
TEST_CASE ("Task 5.6", "Ray, intersection()") {
  
  // ray empty constructor
  Ray r0;
  REQUIRE(r0.origin_ == glm::vec3(0.0f, 0.0f, 0.0f));
  REQUIRE(r0.direction_ == glm::vec3(0.0f, 0.0f, -1.0f));


  // test if ray intersects with sphere (1)
  Sphere s1(glm::vec3(0.0f, 0.0f, 5.0f), 1.0f);
  Ray r1{
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)
  };
  Hitpoint h1 = s1.intersect(r1, 4.0f);
  REQUIRE(h1.has_hit_ == true);
  REQUIRE(h1.distance_ == Approx(4.0f).epsilon(0.001));
  REQUIRE(h1.name_ == "default");
  REQUIRE(h1.color_.r == 1.0f);
  REQUIRE(h1.color_.g == 1.0f);
  REQUIRE(h1.color_.b == 1.0f);
  REQUIRE(h1.intersection_ == glm::vec3(0.0f, 0.0f, 4.0f));
  REQUIRE(h1.ray_direction_ == glm::vec3(0.0f, 0.0f, 1.0f));


  // test if ray intersects with sphere (2)
  Sphere s2(glm::vec3(5.0f, 5.0f, 5.0f), 1.0f);
  Ray r2{
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, -1.0f)
  };
  Hitpoint h2 = s2.intersect(r2, 4.0f);
  REQUIRE(h2.has_hit_ == false);
  REQUIRE(h2.distance_ == Approx(-1.0f).epsilon(0.001)); // error -> returns -1f
  REQUIRE(h2.name_ == "default");
  REQUIRE(h2.color_.r == 1.0f);
  REQUIRE(h2.color_.g == 1.0f);
  REQUIRE(h2.color_.b == 1.0f);
  REQUIRE(h2.intersection_ == glm::vec3(0.0f, 0.0f, 0.0f)); // default hitpoint value
  REQUIRE(h2.ray_direction_ == glm::vec3(0.0f, 0.0f, -1.0f));

}

// test for task 5.6 given in assignemnt
TEST_CASE ("intersect_ray_sphere", "[intersect]") {
  // Ray
  glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
  // ray direction has to be normalized !
  // you can use:
  // v = glm::normalize(some_vector)
  glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
  // Sphere
  glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
  float sphere_radius{1.0f};
  float distance = 0.0f;
  auto result = glm::intersectRaySphere(
    ray_origin, ray_direction, sphere_center,
    sphere_radius * sphere_radius, // squared radius !!!
    distance
  );
  REQUIRE(distance == Approx(4.0f));
}