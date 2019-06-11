#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "sphere.hpp"

float Sphere::area() const {

  // error -> radius must at least be 0
  if (radius_ < 0.0f) {
    return -1.0f;
  }
  
  return 4.0f * M_PI * pow(radius_, 2);
}

float Sphere::volume() const {

  // error -> radius must at least be 0
  if (radius_ < 0.0f) {
    return -1.0f;
  }

  return (4.0f / 3.0f) * M_PI * pow(radius_, 3);
}