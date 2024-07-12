// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_TYPES_FILE_WRITER_H_
#define CAITLYN_CORE_IO_TYPES_FILE_WRITER_H_

#include <fstream>

#include "caitlyn/core/format.h"
#include "caitlyn/core/unicode.h"

namespace cait {

template <typename CharT>
class file_writer;

template <>
class file_writer<char_t> {
public:
  file_writer() = default;
  file_writer(const char_t* filename) : filename_(filename) { open(); }
  file_writer(std::string filename) : filename_(std::move(filename)) { open(); }
  template <typename... Args>
  file_writer(const std::string& str, Args&&... args)
      : filename_{fmt(str, std::forward<Args>(args)...)} {}
  file_writer(const file_writer& other) : filename_{other.filename_} { open(); }
  ~file_writer() { close(); }

public:
  void open() {
    if (filename_.empty()) {
      throw std::ios_base::failure{"Filename is empty"};
    }
    file_.open(filename_, std::ios::out | std::ios::binary | std::ios::app);
    if (!file_.is_open()) {
      throw std::ios_base::failure{"Failed to open file for writing"};
    }
  }

  void close() {
    if (file_.is_open()) {
      file_.close();
    }
  }

public:
  void write(const char_t* data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data;
  }

  void write(const std::string& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data;
  }

  void write(const unicode_char<u8char_t>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data;
  }

  void write(const unicode_string<unicode_char<u8char_t>>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data;
  }

  template <typename... Args>
  void write(const std::string& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_ << fmt(str, std::forward<Args>(args)...);
  }

  void write_line(const char* data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data << get_char(ascii_t::line_feed);
  }

  void write_line(const std::string& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data << get_char(ascii_t::line_feed);
  }

  void write_line(const unicode_char<u8char_t>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data << get_char(ascii_t::line_feed);
  }

  void write_line(const unicode_string<unicode_char<u8char_t>>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data << get_char(ascii_t::line_feed);
  }

  template <typename... Args>
  void write_line(const std::string& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_ << fmt(str, std::forward<Args>(args)...)
          << get_char(ascii_t::line_feed);
  }

  void append(const char_t* data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data;
    file_.flush();
  }

  void append(const std::string& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data;
    file_.flush();
  }

  void append(const unicode_char<u8char_t>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data;
    file_.flush();
  }

  void append(const unicode_string<unicode_char<u8char_t>>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data;
    file_.flush();
  }

  template <typename... Args>
  void append(const std::string& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << fmt(str, std::forward<Args>(args)...);
    file_.flush();
  }

  void append_line(const char* data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data << get_char(ascii_t::line_feed);
  }

  void append_line(const std::string& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data << get_char(ascii_t::line_feed);
  }

  void append_line(const unicode_char<u8char_t>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data << get_char(ascii_t::line_feed);
  }

  void append_line(const unicode_string<unicode_char<u8char_t>>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data << get_char(ascii_t::line_feed);
  }

  template <typename... Args>
  void append_line(const std::string& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << fmt(str, std::forward<Args>(args)...)
          << get_char(ascii_t::line_feed);
    file_.flush();
  }

  void clear() {
    close();
    std::ofstream clear_file{
        filename_, std::ios::out | std::ios::trunc | std::ios::binary};
    if (!clear_file.is_open()) {
      throw std::ios_base::failure{"Failed to open file for clearing"};
    }
    clear_file.close();
    open();
  }

private:
  std::string filename_;
  std::ofstream file_;
};

}  // namespace cait

inline cait::file_writer<cait::u8char_t> operator""_ofile(
    const cait::char_t* filename, const cait::size_t) {
  return cait::file_writer<cait::u8char_t>{filename};
}

#endif  // CAITLYN_CORE_IO_TYPES_FILE_WRITER_H_
