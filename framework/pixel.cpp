#include "pixel.hpp"
#include <ostream>

Pixel::Pixel(unsigned int a, unsigned int b)
  : x(a), y(b), color(0,0,0) {}

void Pixel::print(std::ostream& os) const {
  os << "Pixel[" << (int)x << ',' << (int)y << "]("
     << color.r << ','
     << color.g << ','
     << color.b << ')';
}

std::ostream& operator<<(std::ostream& os, const Pixel& a) {
  std::ostream::sentry se (os);
  if (se) {
    a.print(os);
  }
  return os;
}
