// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
  Color() : r(0.0f), g(0.0f), b(0.0f) {}
  Color(float red, float green, float blue) : r(red), g(green), b(blue) {}

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
  }

  Color& operator-(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
  }

  Color& operator*(float value)
  {
    r *= value;
    g *= value;
    b *= value;
  }

  Color& operator/(float value)
  {
    r /= value;
    g /= value;
    b /= value;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  Color& operator*=(Color const& other)
  {
    r *= other.r;
    g *= other.g;
    b *= other.b;
  }

  Color& operator*=(float value)
  {
    r *= value;
    g *= value;
    b *= value;
  }

  Color& operator/=(float value)
  {
    r /= value;
    g /= value;
    b /= value;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(float value, Color const& color)
  {
    auto tmp(color);
    tmp *= value;
    return tmp;
  }

  friend Color operator*(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp *= b;
    return tmp;
  }

  friend Color operator/(float value, Color const& color)
  {
    auto tmp(color);
    tmp /= value;
    return tmp;
  }

  float r;
  float g;
  float b;
};



#endif //#define BUW_COLOR_HPP
