#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

struct Color {

  float r;
  float g;
  float b;

  Color()
    : r(0.0f), g(0.0f), b(0.0f) {}
  
  Color(float red, float green, float blue)
    : r(red), g(green), b(blue) {}

  friend std::ostream& operator<<(std::ostream& os, Color const& c) {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+(Color const& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-(Color const& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  Color& operator*(float value) {
    r *= value;
    g *= value;
    b *= value;
    return *this;
  }

  Color& operator/(float value) {
    r /= value;
    g /= value;
    b /= value;
    return *this;
  }

  Color& operator+=(Color const& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  Color& operator*=(Color const& other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
  }

  Color& operator*=(float value) {
    r *= value;
    g *= value;
    b *= value;
    return *this;
  }

  Color& operator/=(float value) {
    r /= value;
    g /= value;
    b /= value;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b) {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b) {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(float value, Color const& color) {
    auto tmp(color);
    tmp *= value;
    return tmp;
  }

  friend Color operator*(Color const& a, Color const& b) {
    auto tmp(a);
    tmp *= b;
    return tmp;
  }

  friend Color operator/(float value, Color const& color) {
    auto tmp(color);
    tmp /= value;
    return tmp;
  }

};

#endif //#define COLOR_HPP
