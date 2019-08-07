#include "vec2.hpp"
#include <iostream>

// member addition (u += v)
Vec2 &Vec2::operator +=(Vec2 const &v) {

  x += v.x;
  y += v.y;

  return *this;

}

// member subtraction (u -= v)
Vec2 &Vec2::operator -=(Vec2 const &v) {

  x -= v.x;
  y -= v.y;

  return *this;

}

// member multiplication (u *= s)
Vec2 &Vec2::operator *=(float s) {

  x *= s;
  y *= s;

  return *this;

}

// member division (u /= s)
Vec2 &Vec2::operator /=(float s) {

  if (s == 0.0f) {
    return Vec2{x, y};
  }

  x /= s;
  y /= s;

  return *this;

}

// global addition (u + v)
Vec2 operator +(Vec2 const &u, Vec2 const &v) {
  Vec2 v_new{u.x, u.y};
  v_new += v;
  return v_new;
}

// global subtraction (u - v)
Vec2 operator -(Vec2 const &u, Vec2 const &v) {
  Vec2 v_new{u.x, u.y};
  v_new -= v;
  return v_new;
}

// global division (v / s)
Vec2 operator /(Vec2 const &v, float s) {
  Vec2 v_new{v.x, v.y};
  v_new /= s;
  return v_new;
}

// global multiplication (v * s)
Vec2 operator *(Vec2 const &v, float s) {
  Vec2 v_new{v.x, v.y};
  v_new *= s;
  return v_new;
}

// global multiplication (s * v)
Vec2 operator *(float s, Vec2 const &v) {
  Vec2 v_new{v.x, v.y};
  v_new *= s;
  return v_new;
}