// PpmWriter (C) Andre Schollmeyer, Andreas-C. Bernstein

#include "ppmwriter.hpp"

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

void PpmWriter::write(Pixel const& p) {

  size_t buf_pos = width_* (height_-1-p.y) + p.x;
  std::size_t pos = (sizeof(Color)/sizeof(float)) * buf_pos;

  if (pos + ((sizeof(Color)/sizeof(float)) - 1) > data_.size() || (int)buf_pos < 0) {
    std::cerr << "PpmWriter: Experienced fatal error and could not write position" << std::endl;
  }
  else {
    data_[pos] = (unsigned int)std::max(0.0, std::min(255.0 * p.color.r, 255.0));
    data_[pos+1] = (unsigned int)std::max(0.0, std::min(255.0 * p.color.g, 255.0));
    data_[pos+2] = (unsigned int)std::max(0.0, std::min(255.0 * p.color.b, 255.0));
  }

}

void PpmWriter::save(std::string const& file) {
  file_ = file;
  save();
}

void PpmWriter::save() {

  const std::size_t line_length = 18;

  std::fstream file(file_.c_str(), std::ios::out);
  file.clear();
  file << "P3 "
       << (unsigned int) width_ << " "
       << (unsigned int) height_ << " "
       << 255 << " \n";

  std::size_t pos = 1;
  for (auto i = data_.begin(); i < data_.end(); ++i, ++pos) {
      file << (int)*i << " ";
      if (pos > line_length) {
        file << "\n";
        pos=0;
      }
    }

  file.close();

}