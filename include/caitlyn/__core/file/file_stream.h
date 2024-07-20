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

#ifndef CAITLYN_CORE_FILE_FILE_STREAM_H_
#define CAITLYN_CORE_FILE_FILE_STREAM_H_

#include <fstream>
#include <utility>
#include <vector>

#include "caitlyn/__core/file/basic_file_stream.h"
#include "caitlyn/__core/format.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <>
class basic_file_stream_t<char> {
public:
  basic_file_stream_t() = default;
  basic_file_stream_t(const char* filename) : filename_(filename) { open(); }
  basic_file_stream_t(basic_string_t<char> filename)
      : filename_(std::move(filename)) {
    open();
  }
  template <typename... Args>
  basic_file_stream_t(const basic_string_t<char>& str, Args&&... args)
      : filename_{format(str, std::forward<Args>(args)...)} {
    open();
  }
  basic_file_stream_t(const basic_file_stream_t& other)
      : filename_{other.filename_} {
    open();
  }
  ~basic_file_stream_t() { close(); }

public:
  void open() {
    if (get_filename().empty()) {
      throw std::ios_base::failure{"Filename is empty"};
    }
    file_.open(get_filename(),
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
        get_filename(), std::ios::out | std::ios::trunc | std::ios::binary};
    if (!clear_file.is_open()) {
      throw std::ios_base::failure{"Failed to open file for clearing."};
    }
    clear_file.close();
    open();
  }

  bool eof() const { return file_.eof(); }

  explicit operator bool() const noexcept { return !file_.eof(); }

  void set_position(const std::streampos& position) {
    current_position_ = position;
    file_.clear();
    file_.seekg(current_position_, std::ios::beg);
    if (file_.fail()) {
      throw std::ios_base::failure{"Failed to set position in the file."};
    }
  }

  std::streampos get_position() const { return current_position_; }

public:
  // Reading methods
  basic_string_t<char> read() {
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

  basic_string_t<char> readln(const char delim = def::line_feed[0]) {
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

  void write(const basic_string_t<char>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data;
    file_.flush();
  }

  template <typename T>
  required_t<has_to_string<T>()> write(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data.to_string();
    file_.flush();
  }

  template <typename T>
  required_t<has_str<T>()> write(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data.str();
    file_.flush();
  }

  template <typename... Args>
  void writef(const basic_string_t<char>& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_ << format(str, std::forward<Args>(args)...);
    file_.flush();
  }

  void writeln(const char* data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data << def::line_feed;
    file_.flush();
  }

  void writeln(const basic_string_t<char>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data << def::line_feed;
    file_.flush();
  }

  template <typename T>
  required_t<has_to_string<T>()> writeln(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data.to_string() << def::line_feed;
    file_.flush();
  }

  template <typename T>
  required_t<has_str<T>()> writeln(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data.str() << def::line_feed;
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

  void append(const basic_string_t<char>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data;
    file_.flush();
  }

  template <typename T>
  required_t<has_to_string<T>()> append(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data.to_string();
    file_.flush();
  }

  template <typename T>
  required_t<has_str<T>()> append(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data.str();
    file_.flush();
  }

  template <typename... Args>
  void appendf(const basic_string_t<char>& str, Args&&... args) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << format(str, std::forward<Args>(args)...);
    file_.flush();
  }

  void appendln(const char* data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data << def::line_feed;
    file_.flush();
  }

  void appendln(const basic_string_t<char>& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data << def::line_feed;
    file_.flush();
  }

  template <typename T>
  required_t<has_to_string<T>()> appendln(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data.to_string() << def::line_feed;
    file_.flush();
  }

  template <typename T>
  required_t<has_str<T>()> appendln(const T& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data.str() << def::line_feed;
    file_.flush();
  }

private:
  std::basic_string<char> get_filename() const { return filename_.c_str(); }

private:
  basic_string_t<char> filename_;
  std::basic_fstream<char> file_;
  std::streampos current_position_{};
};

__CAITLYN_GLOBAL_NAMESPACE_END

inline cait::basic_file_stream_t<char> operator""_file(const char* filename,
                                                       const size_t) {
  return cait::basic_file_stream_t<char>{filename};
}

#endif  // CAITLYN_CORE_FILE_FILE_STREAM_H_
