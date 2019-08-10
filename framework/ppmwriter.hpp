// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andre Schollmeyer and Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// PpmWriter
// -----------------------------------------------------------------------------

#ifndef BUW_PPMWRITER_HPP
#define BUW_PPMWRITER_HPP

// header, system
#include <string>
#include <vector>

// header, project
#include <pixel.hpp>

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

#endif // BUW_PPMWRITER
