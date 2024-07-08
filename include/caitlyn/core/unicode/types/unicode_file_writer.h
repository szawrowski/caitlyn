// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_TYPES_UNICODE_FILE_WRITER_H_
#define CAITLYN_CORE_UNICODE_TYPES_UNICODE_FILE_WRITER_H_

#include "caitlyn/core/io/defs/file_definitions.h"
#include "caitlyn/core/unicode/types/unicode_string.h"

__caitlyn_begin_global_namespace

template <typename CharT>
class unicode_file_writer;

using ofile_t = unicode_file_writer<u8char_t>;

template <>
class unicode_file_writer<u8char_t> {
public:
  unicode_file_writer() = default;
  unicode_file_writer(const char_t* filename) : filename_(filename) {
    open();
  }
  unicode_file_writer(string_t filename) : filename_(std::move(filename)) {
    open();
  }
  unicode_file_writer(const unicode_file_writer& other)
      : filename_{other.filename_} {
    open();
  }
  ~unicode_file_writer() { close(); }

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

  void write(const string_t& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data;
  }

  void write(const unichar_t& data) {
    if (!file_.is_open()) {
      open();
    }
    file_ << data;
  }

  void write(const unistr_t& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.write(data.to_std_string().c_str(),
                static_cast<streamsize_t>(data.byte_count()));
  }

  void write_line(const char* data) {
    write(data);
    file_.put('\n');
  }

  void write_line(const string_t& data) {
    write(data);
    file_.put('\n');
  }

  void write_line(const unichar_t& data) {
    write(data);
    file_.put('\n');
  }

  void write_line(const unistr_t& data) {
    write(data);
    file_.put('\n');
  }

  void append(const char_t* data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data;
    file_.flush();
  }

  void append(const string_t& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data;
    file_.flush();
  }

  void append(const unichar_t& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_ << data;
    file_.flush();
  }

  void append(const unistr_t& data) {
    if (!file_.is_open()) {
      open();
    }
    file_.seekp(0, std::ios::end);
    file_.write(data.to_std_string().c_str(),
                static_cast<std::streamsize>(data.byte_count()));
    file_.flush();
  }

  void append_line(const char* data) {
    append(data);
    file_.put('\n');
  }

  void append_line(const std::string& data) {
    append(data);
    file_.put('\n');
  }

  void append_line(const unichar_t& data) {
    append(data);
    file_.put('\n');
  }

  void append_line(const unistr_t& data) {
    append(data);
    file_.put('\n');
  }

  void clear() {
    close();
    ofstream_t clear_file(filename_,
                          std::ios::out | std::ios::trunc | std::ios::binary);
    if (!clear_file.is_open()) {
      throw std::ios_base::failure{"Failed to open file for clearing"};
    }
    clear_file.close();
    open();
  }

private:
  string_t filename_;
  ofstream_t file_;
};

__caitlyn_end_global_namespace

static cait::ofile_t operator""_ofile(const cait::char_t* filename,
                                      const cait::size_t) {
  return cait::ofile_t{filename};
}

#endif  // CAITLYN_CORE_UNICODE_TYPES_UNICODE_FILE_WRITER_H_
