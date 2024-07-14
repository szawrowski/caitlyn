/**
 * This file is part of the Caitlyn library
 * Copyright (C) 2024 Alexander Szawrowski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CAITLYN_CORE_FILE_TYPES_FILE_H_
#define CAITLYN_CORE_FILE_TYPES_FILE_H_

#include <fstream>
#include <utility>
#include <vector>

#include "caitlyn/core/format.h"

namespace cait {

template <typename CharT>
class file_t;

template <>
class file_t<char> {
public:
  file_t() = default;
  file_t(const char* filename) : filename_(filename) { open(); }
  file_t(std::string filename) : filename_(std::move(filename)) { open(); }
  template <typename... Args>
  file_t(const std::string& str, Args&&... args)
      : filename_{format(str, std::forward<Args>(args)...)} {
    open();
  }
  file_t(const file_t& other) : filename_{other.filename_} { open(); }
  ~file_t() { close(); }

public:
  void open() {
    if (filename_.empty()) {
      throw std::ios_base::failure{"Filename is empty"};
    }
    file_.open(filename_,
               std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
    if (!file_.is_open()) {
      throw std::ios_base::failure{"Failed to open file for writing."};
    }
  }

  void close() {
    if (file_.is_open()) {
      file_.close();
    }
  }

  void erase() {
    close();
    std::ofstream clear_file{
        filename_, std::ios::out | std::ios::trunc | std::ios::binary};
    if (!clear_file.is_open()) {
      throw std::ios_base::failure{"Failed to open file for clearing."};
    }
    clear_file.close();
    open();
  }

  __caitlyn_nodiscard bool eof() const { return file_.eof(); }

  explicit operator bool() const noexcept { return !file_.eof(); }

  void set_position(const std::streampos& position) {
    current_position_ = position;
    file_.clear();
    file_.seekg(current_position_, std::ios::beg);
    if (file_.fail()) {
      throw std::ios_base::failure{"Failed to set position in the file."};
    }
  }

  __caitlyn_nodiscard std::streampos get_position() const {
    return current_position_;
  }

public:
  // Reading methods
  __caitlyn_nodiscard std::string read() {
    if (!file_.is_open()) {
      open();
    }
    file_.seekg(0, std::ios::end);
    const std::streamsize size = file_.tellg();
    file_.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (file_.read(buffer.data(), size)) {
      return buffer.data();
    }
    return {};
  }

  __caitlyn_nodiscard std::string read_line(const char delim = '\n') {
    if (!file_.is_open()) {
      open();
    }
    if (file_.eof()) {
      return {};
    }
    if (file_.fail() || file_.bad()) {
      throw std::ios_base::failure{"Stream error encountered before reading."};
    }
    file_.clear();
    file_.seekg(current_position_, std::ios::beg);

    std::ostringstream result;
    char ch;
    while (file_.get(ch)) {
      if (ch == delim) {
        current_position_ = file_.tellg();
        return result.str();
      }
      result << ch;
    }
    if (file_.eof()) {
      current_position_ = file_.tellg();
      return result.str();
    }
    if (file_.fail() || file_.bad()) {
      throw std::ios_base::failure{"Stream failed while reading."};
    }
    return result.str();
  }

  void write(const char* data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data;
    file_.flush();
  }

  void write(const std::string& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data;
    file_.flush();
  }

  template <typename T>
  required_t<is_convertible_to_string<T>()> write(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data.to_string();
    file_.flush();
  }

  template <typename... Args>
  void write(const std::string& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_ << format(str, std::forward<Args>(args)...);
    file_.flush();
  }

  void write_line(const char* data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data << get_char(ascii_t::line_feed);
    file_.flush();
  }

  void write_line(const std::string& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data << get_char(ascii_t::line_feed);
    file_.flush();
  }

  template <typename T>
  required_t<is_convertible_to_string<T>()> write_line(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data.to_string() << get_char(ascii_t::line_feed);
    file_.flush();
  }

  template <typename... Args>
  void write_line(const std::string& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_ << format(str, std::forward<Args>(args)...)
          << get_char(ascii_t::line_feed);
    file_.flush();
  }

  void append(const char* data) {
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

  template <typename T>
  required_t<is_convertible_to_string<T>()> append(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data.to_string();
    file_.flush();
  }

  template <typename... Args>
  void append(const std::string& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << format(str, std::forward<Args>(args)...);
    file_.flush();
  }

  void append_line(const char* data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data << get_char(ascii_t::line_feed);
    file_.flush();
  }

  void append_line(const std::string& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data << get_char(ascii_t::line_feed);
    file_.flush();
  }

  template <typename T>
  required_t<is_convertible_to_string<T>()> append_line(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data.to_string() << get_char(ascii_t::line_feed);
    file_.flush();
  }

  template <typename... Args>
  void append_line(const std::string& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << format(str, std::forward<Args>(args)...)
          << get_char(ascii_t::line_feed);
    file_.flush();
  }

private:
  std::string filename_;
  std::fstream file_;
  std::streampos current_position_{};
};

}  // namespace cait

inline cait::file_t<char> operator""_file(const char* filename, const size_t) {
  return cait::file_t<char>{filename};
}

#endif  // CAITLYN_CORE_FILE_TYPES_FILE_H_
