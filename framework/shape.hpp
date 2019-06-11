#ifndef SHAPE_HPP
#define SHAPE_HPP

class Shape {

  public:
    virtual int area() const = 0; // flaeche
    virtual int volume() const = 0; // oberfläche
 
};

#endif // define SHAPE_HPP