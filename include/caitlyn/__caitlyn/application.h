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

#ifndef CAITLYN_APPLICATION_H_
#define CAITLYN_APPLICATION_H_

#include <cstring>
#include <stdexcept>
#include <vector>

#include "caitlyn/__caitlyn/config.h"
#include "caitlyn/__caitlyn/types.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

class application_t {
public:
  static const application_t* init() {
    if (initialized_) {
      throw std::runtime_error("caitlyn::init can only be called once.");
    }
    initialized_ = true;
    return new application_t{};
  }

  static const application_t* init(const int& argc, const char** argv) {
    if (initialized_) {
      throw std::runtime_error("caitlyn::init can only be called once.");
    }
    initialized_ = true;
    return new application_t{argc, argv};
  }

  const std::vector<const char*>& get_args() const { return args_; }

  const char* get_system() const { return system_name_; }
  const char* get_compiler() const { return compiler_; }
  const char* get_caitlyn_info() const { return lib_version_; }

private:
  application_t()
      : lib_version_{__CAITLYN_VERSION},
        system_name_{__CAITLYN_OS_NAME},
        compiler_{__CAITLYN_COMPILER_VERSION} {
    configure();
  }

  application_t(const int argc, const char** argv)
      : lib_version_{__CAITLYN_VERSION},
        system_name_{__CAITLYN_OS_NAME},
        compiler_{__CAITLYN_COMPILER_VERSION} {
    if (argc > 0) {
      args_.reserve(argc);
      for (int i = 0; i < argc; ++i) {
        auto arg_copy = new char[std::strlen(argv[i]) + 1];
        std::strcpy(arg_copy, argv[i]);
        args_.emplace_back(arg_copy);
      }
    }
    configure();
  }

  ~application_t() {
    for (const char* arg : args_) {
      delete[] arg;
    }
  }

private:
  static void configure() {
#ifdef __CAITLYN_OS_WINDOWS
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
  }

private:
  std::vector<const char*> args_{};
  const char* lib_version_;
  const char* system_name_;
  const char* compiler_;
  static bool initialized_;
};

bool application_t::initialized_ = false;

__CAITLYN_DETAIL_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_APPLICATION_H_
