#include "mat2.hpp"

#include <iostream>
#include <math.h>

// member multiplication (m1 *= m)
Mat2 &Mat2::operator *=(const Mat2& m) {

  float a_temp = a * m.a + b * m.c;
  float b_temp = a * m.b + b * m.d;
  float c_temp = c * m.a + d * m.c;
  float d_temp = c * m.b + d * m.d;

  a = a_temp;
  b = b_temp;
  c = c_temp;
  d = d_temp;

  return *this;

}

// global multiplication (m1 * m2)
Mat2 operator *(const Mat2& m1, const Mat2& m2) {
  Mat2 m{m1.a, m1.b, m1.c, m1.d};
  m *= m2;
  return m;
}

// global multiplication (m * v)
Vec2 operator*(const Mat2& m, const Vec2& v) {
  return Vec2{m.a * v.x + m.b * v.y,
              m.c * v.x + m.d * v.y};
}

// global multiplication (v * m)
Vec2 operator*(const Vec2& v, const Mat2& m) {
  return m * v;
}

// return determinant
float Mat2::det() const {

  return a*d - c*b;

}

// return matrix inverse
Mat2 inverse(const Mat2& m) {
  
  // determinant
  float det = m.det();

  // no inverse
  if (det == 0) {
    return Mat2{m.a, m.b,
                m.c, m.d};
  }

  return Mat2{m.d / det, -m.b / det,
              -m.c / det, m.a / det};

}

// mirror matrix
Mat2 transpose(const Mat2& m) {

  return Mat2{m.a, m.c, m.b, m.d};

}

// rotate matrix with degree
Mat2 make_rotation_mat2(float phi) {

  return Mat2{cos(phi), -sin(phi),
              sin(phi), cos(phi)};

}