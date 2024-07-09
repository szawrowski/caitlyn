// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_TYPES_UNICODE_FILE_READER_H_
#define CAITLYN_CORE_UNICODE_TYPES_UNICODE_FILE_READER_H_

#include "caitlyn/core/io/types/file.h"
#include "caitlyn/core/string/types/types.h"
#include "caitlyn/core/unicode/types/unicode_string.h"

__caitlyn_begin_global_namespace

template <typename CharT>
class unicode_file_reader;

using ifile_t = unicode_file_reader<u8char_t>;

template <>
class unicode_file_reader<u8char_t> {
public:
  unicode_file_reader() = default;
  unicode_file_reader(const char_t* filename) : filename_(filename) {
    open();
  }
  unicode_file_reader(string_t filename) : filename_(std::move(filename)) {
    open();
  }
  unicode_file_reader(const unicode_file_reader& other)
      : filename_{other.filename_} {
    open();
  }
  ~unicode_file_reader() { close(); }

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
  __caitlyn_nodiscard unistr_t read() {
    if (!file_.is_open()) {
      open();
    }
    file_.seekg(0, std::ios::end);
    const streamsize_t size = file_.tellg();
    file_.seekg(0, std::ios::beg);

    vector_t<char_t> buffer(size);
    if (file_.read(buffer.data(), size)) {
      return unistr_t{string_t(buffer.data(), size)};
    }
    return unistr_t{};
  }

  __caitlyn_nodiscard unistr_t read_line() {
    if (!file_.is_open()) {
      open();
    }
    string_t line;
    if (std::getline(file_, line)) {
      return unistr_t{line};
    }
    return unistr_t{};
  }

private:
  string_t filename_;
  ifstream_t file_;
};

__caitlyn_end_global_namespace

static cait::ifile_t operator""_ifile(const cait::char_t* filename,
                                      const cait::size_t) {
  return cait::ifile_t{filename};
}

#endif  // CAITLYN_CORE_UNICODE_TYPES_UNICODE_FILE_READER_H_
