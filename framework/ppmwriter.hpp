// PpmWriter (C) Andre Schollmeyer, Andreas-C. Bernstein

#ifndef PPMWRITER_HPP
#define PPMWRITER_HPP

#include "pixel.hpp"

#include <string>
#include <vector>

class PpmWriter {

  public:

    PpmWriter(unsigned int w, unsigned int h)
      : file_("untitled.ppm"), width_(w), height_(h) {
      data_.resize(w * h * (sizeof(Color)/sizeof(float)));
    }

    PpmWriter(unsigned int w, unsigned int h, std::string const& file)
      : file_(file), width_(w), height_(h) {
      data_.resize(w * h * (sizeof(Color)/sizeof(float)));
    }

    void write(Pixel const& p);
    void save(std::string const& file);
    void save();

  private:
  
    std::string file_;
    std::vector<unsigned int> data_;
    unsigned int width_;
    unsigned int height_;

};

#endif // PPMWRITER_HPP