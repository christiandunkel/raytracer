#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <iosfwd>
#include <color.hpp>

class Pixel {

  public :

    unsigned int x = 0;
    unsigned int y = 0;
    Color color = {1.0, 1.0, 1.0};

    Pixel(unsigned int = 0, unsigned int = 0);
    void print(std::ostream&) const;

};

std::ostream& operator<<(std::ostream&, const Pixel&);

#endif // PIXEL_HPP
