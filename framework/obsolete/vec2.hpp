#ifndef VEC2_HPP
#define VEC2_HPP

struct Vec2 {

  // member variables
  float x = 0.0f;
  float y = 0.0f;

  // member operators
  Vec2 &operator +=(Vec2 const &v);
  Vec2 &operator -=(Vec2 const &v);
  Vec2 &operator *=(float s);
  Vec2 &operator /=(float s);

};

// global operators
Vec2 operator +(Vec2 const &u, Vec2 const &v);
Vec2 operator -(Vec2 const &u, Vec2 const &v);
Vec2 operator /(Vec2 const &v, float s);
Vec2 operator *(Vec2 const &v, float s);
Vec2 operator *(float s, Vec2 const &v);

#endif // VEC2_HPP