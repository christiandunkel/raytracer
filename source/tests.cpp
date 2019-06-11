#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>

#include "sphere.hpp"
#include "box.hpp"

int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}


TEST_CASE("Task 5.2", "Sphere, Box (area(), volume())") {

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
  REQUIRE(s3.area() == Approx(-1.0f).epsilon(0.001)); // error -> return -1f
  REQUIRE(s3.volume() == Approx(-1.0f).epsilon(0.001)); // error -> return -1f

  // box constructors
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