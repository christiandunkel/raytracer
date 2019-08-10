#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include "sphere.hpp"
#include "box.hpp"
#include "triangle.hpp"
#include "ray.hpp"
#include "sdfManager.hpp"
#include "renderer.hpp"

int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}

TEST_CASE("Task 5.2", "Sphere, Box, Triangle methods area(), volume()") {

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

  // triangle
  Triangle t1;
  REQUIRE(t1.area() == Approx(0.0f).epsilon(0.001));
  
  Triangle t2(glm::vec3(1.0f, 1.0f, 0.0f),
              glm::vec3(-2.0f, 4.0f, 1.0f),
              glm::vec3(-2.0f, -2.0f, 2.0f));
  REQUIRE(t2.area() == Approx(10.17f).epsilon(0.001));

}


/*
  create sphere object
    - calls base class constructor (shape) first, then constructor of sphere
    - if there's an initializing list, constructor of base class is 
        called at beginning of list
    - can be defined as point in list as well e.g. Shape(), Shape(string name),..
 */
TEST_CASE("Task 5.3", "name_, color_ attributes") {

  /*  DON'T TEST, excluded since task 6.3, 
      since Color color_ has been replaced by Material material_


  // sphere
  Sphere s1;
  REQUIRE(s1.get_name() == "default");
  REQUIRE(s1.get_color().r == Approx(1.0f).epsilon(0.001));
  REQUIRE(s1.get_color().g == Approx(1.0f).epsilon(0.001));
  REQUIRE(s1.get_color().b == Approx(1.0f).epsilon(0.001));

  Sphere s2(glm::vec3(0.5f, 0.3f, 5.0f), 25.0f, Color(0.3f, 0.4f, 0.5f));
  REQUIRE(s2.get_name() == "default");
  REQUIRE(s2.get_color().r == Approx(0.3f).epsilon(0.001));
  REQUIRE(s2.get_color().g == Approx(0.4f).epsilon(0.001));
  REQUIRE(s2.get_color().b == Approx(0.5f).epsilon(0.001));

  Sphere s3(glm::vec3(0.5f, 0.3f, 5.0f), 25.0f, Color(0.3f, 0.4f, 0.5f), "test");
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

  Box b2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), Color(0.3f, 0.4f, 0.5f));
  REQUIRE(b2.get_name() == "default");
  REQUIRE(b2.get_color().r == Approx(0.3f).epsilon(0.001));
  REQUIRE(b2.get_color().g == Approx(0.4f).epsilon(0.001));
  REQUIRE(b2.get_color().b == Approx(0.5f).epsilon(0.001));

  Box b3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), Color(0.3f, 0.4f, 0.5f), "test");
  REQUIRE(b3.get_name() == "test");
  REQUIRE(b3.get_color().r == Approx(0.3f).epsilon(0.001));
  REQUIRE(b3.get_color().g == Approx(0.4f).epsilon(0.001));
  REQUIRE(b3.get_color().b == Approx(0.5f).epsilon(0.001));*/

}




/*
  override
    - overriding would happen regardless, 
      but 'override' makes sure that the inhterited method is virtual
    --> if it is not virtual => compile error
    
  */
TEST_CASE("Task 5.5", "Sphere, Box method print()") {

  std::cout << Sphere() << std::endl; // print sphere
  std::cout << Box("test name") << std::endl; // print box

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

  Triangle t1(
    glm::vec3(0.0f, 0.0f, 2.0f),
    glm::vec3(2.0f, 0.0f, 2.0f),
    glm::vec3(0.0f, 2.0f, 2.0f)
  );

  Hitpoint h3 = t1.intersect(r1);
  REQUIRE(h3.has_hit_ == true);
  REQUIRE(h3.distance_ == 2.0f);

}

// test for task 5.6 given in assignemnt
TEST_CASE("intersect_ray_sphere", "[intersect]") {
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



/*

  TASK 5.7

  dynamic variable = 
    variable whose address is determined when the program is run
  static variable = 
    already known at compilation time, 
    has memory reseved for it at compilation time

  std::shared_ptr
    - smart pointer
    - retains shared ownership of an object thrugh pointer
    - several smart pointers may own the same object
    - object is destroyed, when:
      - last smart pointer owning it is destroyed
      - last smart pointer owning it is assigned another pointer via = o. reset()
    - can own object while storing pointer to another
      - for example, can be used to point to an object's member, while still owning the object

  std::make_shared
    - construct T object and wrap it in smart pointer

*/

TEST_CASE("Task 5.7", "Static vs. Dynamic Type of a variable") {

  /*
   * red plastic definition:
   * http://devernay.free.fr/cours/opengl/materials.html
   */

  std::shared_ptr<Material> red_plastic(new Material{
    "red_plastic",
    Color{0.0f, 0.0f, 0.0f},
    Color{0.5f, 0.0f, 0.0f}, // red diffuse color
    Color{0.7f, 0.6f, 0.6f},
    0.25f * 128.0f // multiply with 128, because standards
  });

  glm::vec3 position{0.0f, 0.0f, 0.0f};
  std::shared_ptr<Sphere> s1 = 
    std::make_shared<Sphere>(position, 1.2f, red_plastic, "sphere0");
  /* 
    static pointer -> static pointer
      - in compilation-time known
      - can use all methods of sphere
  */

  std::shared_ptr<Shape> s2 =
    std::make_shared<Sphere>(position, 1.2f, red_plastic, "sphere1");
  /* 
      static pointer -> to dynamic object
       - in run-time looks for Sphere object
       - can only run methods of Sphere 
         (but virtual methods overriden by sphere still work) 
  */

  s1->print(std::cout);
  s2->print(std::cout);
  // s1 and s2 have the same content (except for the name),
  // but are two different objects
}



/* 
  order of constructor / destructor calls
    1. constructor s1 (shape)
    2. constructor s1 (sphere)
    3. constructor s2 (shape)
    4. constructor s2 (sphere)
    5. destructor s1 (sphere)
    6. destructor s1 (shape)
    7. destructor s2 (sphere)
    8. destructor s2 (shape)

  on removing 'virtual' of base class 'shape' (and 'override' tags)
    - destructor for sphere3 is called only once,
      since it's not linked with child class
    - because:
        shape -> sphere
        shape delete -> calls size_of for size of object 
            -> gets size of base class, because not virtual 
            -> only deletes base object 
  
    1. constructor s1 (shape)
    2. constructor s1 (sphere)
    3. constructor s2 (shape)
    4. constructor s2 (sphere)
    5. destructor s1 (sphere)
    6. destructor s1 (shape)
    7. destructor s2 (shape)

  */
TEST_CASE("Task 5.8", "Virtual destructor") {

  /*
   * red plastic definition:
   * http://devernay.free.fr/cours/opengl/materials.html
   */

  std::shared_ptr<Material> red_plastic(new Material{
    "red_plastic",
    Color{0.0f, 0.0f, 0.0f},
    Color{0.5f, 0.0f, 0.0f}, // red diffuse color
    Color{0.7f, 0.6f, 0.6f},
    0.25f * 128.0f // multiply with 128, because standards
  });

  glm::vec3 position{0.0f, 0.0f, 0.0f};

  Sphere* s1 = new Sphere{position, 1.2f, red_plastic, "sphere2"};
  Shape* s2 = new Sphere{position, 1.2f, red_plastic, "sphere3"};

  s1->print(std::cout);
  s2->print(std::cout);

  delete s1;
  delete s2;
}



TEST_CASE("Task 6.3", "Box intersect()") {

  // box vertically, directly above 0/0/0
  // ray goes vertically upwards -> hits
  Box b1(
    glm::vec3(-1.0f, 2.0f, -1.0f),
    glm::vec3(1.0f, 4.0f, 1.0f)
  );
  Ray r1{
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
  };
  Hitpoint h1 = b1.intersect(r1, 4.0f);
  REQUIRE(h1.has_hit_ == true);

  REQUIRE(h1.intersection_ == glm::vec3(0.0f, 2.0f, 0.0f));



  // ray goes sideways -> misses
  Ray r2{
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f)
  };
  Hitpoint h2 = b1.intersect(r2, 4.0f);
  REQUIRE(h2.has_hit_ == false);

}

TEST_CASE("Task 6.4", "Material DTO") {
  Material m1;
  
  REQUIRE(m1.name_ == "");

  REQUIRE(m1.ka_.r == Approx(1.0f).epsilon(0.001));
  REQUIRE(m1.ka_.g == Approx(1.0f).epsilon(0.001));
  REQUIRE(m1.ka_.b == Approx(1.0f).epsilon(0.001));

  REQUIRE(m1.kd_.r == Approx(1.0f).epsilon(0.001));
  REQUIRE(m1.kd_.g == Approx(1.0f).epsilon(0.001));
  REQUIRE(m1.kd_.b == Approx(1.0f).epsilon(0.001));

  REQUIRE(m1.ks_.r == Approx(1.0f).epsilon(0.001));
  REQUIRE(m1.ks_.g == Approx(1.0f).epsilon(0.001));
  REQUIRE(m1.ks_.b == Approx(1.0f).epsilon(0.001));

  REQUIRE(m1.m_ == Approx(0.0f).epsilon(0.001));

  Material m2{"Material2", {0.5f, 1.0f, 0.2f}, {1.0f, 0.1f, 1.0f}, {1.0f, 1.0f, 0.5f}, 5.0f};
  
  REQUIRE(m2.name_ == "Material2");

  REQUIRE(m2.ka_.r == Approx(0.5f).epsilon(0.001));
  REQUIRE(m2.ka_.g == Approx(1.0f).epsilon(0.001));
  REQUIRE(m2.ka_.b == Approx(0.2f).epsilon(0.001));

  REQUIRE(m2.kd_.r == Approx(1.0f).epsilon(0.001));
  REQUIRE(m2.kd_.g == Approx(0.1f).epsilon(0.001));
  REQUIRE(m2.kd_.b == Approx(1.0f).epsilon(0.001));

  REQUIRE(m2.ks_.r == Approx(1.0f).epsilon(0.001));
  REQUIRE(m2.ks_.g == Approx(1.0f).epsilon(0.001));
  REQUIRE(m2.ks_.b == Approx(0.5f).epsilon(0.001));

  REQUIRE(m2.m_ == Approx(5.0f).epsilon(0.001));
}

TEST_CASE("Task 6.5", "") {
  SdfManager sdfs;

  std::unique_ptr<Scene> scene_nullptr = sdfs.parse("non_existing_path/file_name.nope");
  REQUIRE(scene_nullptr == nullptr);

  std::unique_ptr<Scene> scene = sdfs.parse("resource/materials_test.sdf");

  // BEST CASE: 1
  // AVERAGE CASE: n/2
  // WORST CASE: n
  // linear time

  auto red_material = scene->find_material("red");

  REQUIRE(red_material->name_ == "red");
  REQUIRE(red_material->ka_.r == Approx(1.0f).epsilon(0.001));
  REQUIRE(red_material->ka_.g == Approx(0.0f).epsilon(0.001));
  REQUIRE(red_material->ka_.b == Approx(0.0f).epsilon(0.001));

  REQUIRE(red_material->kd_.r == Approx(1.0f).epsilon(0.001));
  REQUIRE(red_material->kd_.g == Approx(0.0f).epsilon(0.001));
  REQUIRE(red_material->kd_.b == Approx(0.0f).epsilon(0.001));

  REQUIRE(red_material->ks_.r == Approx(1.0f).epsilon(0.001));
  REQUIRE(red_material->ks_.g == Approx(0.0f).epsilon(0.001));
  REQUIRE(red_material->ks_.b == Approx(0.0f).epsilon(0.001));

  REQUIRE(red_material->m_ == Approx(20.0f).epsilon(0.001));

  // BEST CASE: 1
  // AVERAGE CASE: O(log(n) * k)
  // WORST CASE: O(log(n) * k)
  // k = time complexity of comparing two elements
  // logarithmic time (Red-Black Tree by default)

  auto green_material = scene->find_material("green");

  REQUIRE(green_material->name_ == "green");
  REQUIRE(green_material->ka_.r == Approx(0.0f).epsilon(0.001));
  REQUIRE(green_material->ka_.g == Approx(1.0f).epsilon(0.001));
  REQUIRE(green_material->ka_.b == Approx(0.0f).epsilon(0.001));

  REQUIRE(green_material->kd_.r == Approx(0.0f).epsilon(0.001));
  REQUIRE(green_material->kd_.g == Approx(1.0f).epsilon(0.001));
  REQUIRE(green_material->kd_.b == Approx(0.0f).epsilon(0.001));

  REQUIRE(green_material->ks_.r == Approx(0.0f).epsilon(0.001));
  REQUIRE(green_material->ks_.g == Approx(1.0f).epsilon(0.001));
  REQUIRE(green_material->ks_.b == Approx(0.0f).epsilon(0.001));

  REQUIRE(green_material->m_ == Approx(50.0f).epsilon(0.001));

  // BEST CASE: 1
  // AVERAGE CASE: O(log(n) * k)
  // WORST CASE: O(log(n) * k)
  // k = time complexity of comparing two elements
  // logarithmic time (Red-Black Tree by default)

  auto blue_material = scene->find_material("blue");

  REQUIRE(blue_material->name_ == "blue");
  REQUIRE(blue_material->ka_.r == Approx(0.0f).epsilon(0.001));
  REQUIRE(blue_material->ka_.g == Approx(0.0f).epsilon(0.001));
  REQUIRE(blue_material->ka_.b == Approx(1.0f).epsilon(0.001));

  REQUIRE(blue_material->kd_.r == Approx(0.0f).epsilon(0.001));
  REQUIRE(blue_material->kd_.g == Approx(0.0f).epsilon(0.001));
  REQUIRE(blue_material->kd_.b == Approx(1.0f).epsilon(0.001));

  REQUIRE(blue_material->ks_.r == Approx(0.0f).epsilon(0.001));
  REQUIRE(blue_material->ks_.g == Approx(0.0f).epsilon(0.001));
  REQUIRE(blue_material->ks_.b == Approx(1.0f).epsilon(0.001));

  REQUIRE(blue_material->m_ == Approx(10.0f).epsilon(0.001));

  // box
  auto box_rbottom = scene->find_shape("rbottom");
  auto box = std::static_pointer_cast<Box>(box_rbottom);

  REQUIRE(box->get_name() == "rbottom");
  REQUIRE(box->get_min().x == Approx(-100.0f).epsilon(0.001));
  REQUIRE(box->get_min().y == Approx(-80.0f).epsilon(0.001));
  REQUIRE(box->get_min().z == Approx(-200.0f).epsilon(0.001));

  REQUIRE(box->get_max().x == Approx(100.0f).epsilon(0.001));
  REQUIRE(box->get_max().y == Approx(80.0f).epsilon(0.001));
  REQUIRE(box->get_max().z == Approx(-100.0f).epsilon(0.001));

  REQUIRE(box->get_material()->kd_.r == Approx(1.0f).epsilon(0.001));
  REQUIRE(box->get_material()->kd_.g == Approx(0.0f).epsilon(0.001));
  REQUIRE(box->get_material()->kd_.b == Approx(0.0f).epsilon(0.001));

  // sphere
  auto sphere_rbottom = scene->find_shape("bsphere");
  auto sphere = std::static_pointer_cast<Sphere>(sphere_rbottom);

  REQUIRE(sphere->get_name() == "bsphere");
  REQUIRE(sphere->get_middle().x == Approx(0.0f).epsilon(0.001));
  REQUIRE(sphere->get_middle().y == Approx(0.0f).epsilon(0.001));
  REQUIRE(sphere->get_middle().z == Approx(-100.0f).epsilon(0.001));

  REQUIRE(sphere->get_radius() == Approx(50.0f).epsilon(0.001));

  REQUIRE(sphere->get_material()->kd_.r == Approx(0.0f).epsilon(0.001));
  REQUIRE(sphere->get_material()->kd_.g == Approx(0.0f).epsilon(0.001));
  REQUIRE(sphere->get_material()->kd_.b == Approx(1.0f).epsilon(0.001));

  // triangle
  auto triangle_rbottom = scene->find_shape("btriangle");
  auto triangle = std::static_pointer_cast<Triangle>(triangle_rbottom);

  REQUIRE(triangle->get_name() == "btriangle");
  REQUIRE(triangle->get_a().x == Approx(-100.0f).epsilon(0.001));
  REQUIRE(triangle->get_a().y == Approx(-80.0f).epsilon(0.001));
  REQUIRE(triangle->get_a().z == Approx(-200.0f).epsilon(0.001));

  REQUIRE(triangle->get_b().x == Approx(100.0f).epsilon(0.001));
  REQUIRE(triangle->get_b().y == Approx(80.0f).epsilon(0.001));
  REQUIRE(triangle->get_b().z == Approx(-100.0f).epsilon(0.001));

  REQUIRE(triangle->get_c().x == Approx(0.0f).epsilon(0.001));
  REQUIRE(triangle->get_c().y == Approx(0.0f).epsilon(0.001));
  REQUIRE(triangle->get_c().z == Approx(0.0f).epsilon(0.001));

  REQUIRE(triangle->get_material()->kd_.r == Approx(0.0f).epsilon(0.001));
  REQUIRE(triangle->get_material()->kd_.g == Approx(1.0f).epsilon(0.001));
  REQUIRE(triangle->get_material()->kd_.b == Approx(0.0f).epsilon(0.001));

  // diffuse point light
  auto light_sun = scene->find_light("sun");
  auto sun = std::static_pointer_cast<DiffusePointLight>(light_sun);

  REQUIRE(sun->pos_.x == Approx(1000.0f).epsilon(0.001));
  REQUIRE(sun->pos_.y == Approx(700.0f).epsilon(0.001));
  REQUIRE(sun->pos_.z == Approx(0.0f).epsilon(0.001));

  REQUIRE(sun->color_.r == Approx(0.2f).epsilon(0.001));
  REQUIRE(sun->color_.g == Approx(0.2f).epsilon(0.001));
  REQUIRE(sun->color_.b == Approx(0.2f).epsilon(0.001));

  REQUIRE(sun->intensity_ == Approx(100.0f).epsilon(0.001));

  // ambient light
  auto light_ambient = scene->find_light("ambient1");
  auto ambient = std::static_pointer_cast<AmbientLight>(light_ambient);

  REQUIRE(ambient->color_.r == Approx(0.3f).epsilon(0.001));
  REQUIRE(ambient->color_.g == Approx(0.2f).epsilon(0.001));
  REQUIRE(ambient->color_.b == Approx(0.6f).epsilon(0.001));

  REQUIRE(ambient->intensity_ == Approx(5.0f).epsilon(0.001));

  // camera without position
  auto c1 = scene->find_camera("eye");

  REQUIRE(c1->name_ == "eye");
  REQUIRE(c1->fov_ == Approx(45.0f).epsilon(0.001));

  // camera with position
  auto c2 = scene->find_camera("eye2");

  REQUIRE(c2->name_ == "eye2");
  REQUIRE(c2->fov_ == Approx(45.0f).epsilon(0.001));
  REQUIRE(c2->pos_.x == Approx(0.0f).epsilon(0.001));
  REQUIRE(c2->pos_.y == Approx(0.0f).epsilon(0.001));
  REQUIRE(c2->pos_.z == Approx(-3.0f).epsilon(0.001));

  auto r1 = scene->renderer_vec_.at(0);

  REQUIRE(r1.is_valid() == true);

  auto r2 = scene->renderer_vec_.at(1);

  REQUIRE(r2.is_valid() == false);
}