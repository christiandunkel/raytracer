#ifndef MAT2_HPP
#define MAT2_HPP

#include "vec2.hpp"

// Mat2 class definition
struct Mat2 {

  // matrix member values in order
  // equals identity matrix if not initialised
  float a = 1.0f, b = 0.0f;
  float c = 0.0f, d = 1.0f;

  float det() const;

  // member operators
  Mat2& operator*=(Mat2 const& m);

};

// global operators
Mat2 operator*(const Mat2& m1, const Mat2& m2);
Vec2 operator*(const Mat2& m, const Vec2& v);
Vec2 operator*(const Vec2& v, const Mat2& m);

// matrix calculation functions
Mat2 inverse(const Mat2& m);
Mat2 transpose(const Mat2& m);
Mat2 make_rotation_mat2(float phi);

#endif // MAT2_HPP