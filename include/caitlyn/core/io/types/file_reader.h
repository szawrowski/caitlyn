// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_TYPES_FILE_READER_H_
#define CAITLYN_CORE_IO_TYPES_FILE_READER_H_

#include <fstream>

#include "caitlyn/core/format/format.h"
#include "caitlyn/core/unicode/types/unicode_string.h"

namespace cait {

template <typename CharT>
class file_reader;

template <>
class file_reader<char_t> {
public:
  file_reader() = default;
  file_reader(const char_t* filename) : filename_(filename) { open(); }
  file_reader(std::string filename) : filename_(std::move(filename)) { open(); }
  template <typename... Args>
  file_reader(const std::string& str, Args&&... args)
      : filename_{format(str, std::forward<Args>(args)...)} {}
  file_reader(const file_reader& other) : filename_{other.filename_} { open(); }
  ~file_reader() { close(); }

public:
  void open() {
    if (filename_.empty()) {
      throw std::ios_base::failure{"Filename is empty"};
    }
    file_.open(filename_, std::ios::in | std::ios::binary);
    if (!file_.is_open()) {
      throw std::ios_base::failure{"Failed to open file for reading"};
    }
  }

  void close() {
    if (file_.is_open()) {
      file_.close();
    }
  }

public:
  __caitlyn_nodiscard unicode_string<unicode_char<u8char_t>> read() {
    if (!file_.is_open()) {
      open();
    }
    file_.seekg(0, std::ios::end);
    const streamsize_t size = file_.tellg();
    file_.seekg(0, std::ios::beg);

    std::vector<char_t> buffer(size);
    if (file_.read(buffer.data(), size)) {
      return unicode_string<unicode_char<u8char_t>>{
          std::string(buffer.data(), size)};
    }
    return unicode_string<unicode_char<u8char_t>>{};
  }

  __caitlyn_nodiscard unicode_string<unicode_char<u8char_t>> read_line() {
    if (!file_.is_open()) {
      open();
    }
    std::string line;
    if (std::getline(file_, line)) {
      return unicode_string<unicode_char<u8char_t>>{line};
    }
    return unicode_string<unicode_char<u8char_t>>{};
  }

private:
  std::string filename_;
  std::ifstream file_;
};

}  // namespace cait

static cait::file_reader<cait::u8char_t> operator""_ifile(
    const cait::char_t* filename, const cait::size_t) {
  return cait::file_reader<cait::u8char_t>{filename};
}

#endif  // CAITLYN_CORE_IO_TYPES_FILE_READER_H_