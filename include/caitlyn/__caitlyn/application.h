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

#include "caitlyn/__caitlyn/config.h"
#include "caitlyn/__caitlyn/types.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

class application_t {
public:
  static std::unique_ptr<application_t> init() {
    if (initialized_) {
      throw std::runtime_error("caitlyn::init can only be called once.");
    }
    initialized_ = true;
    return std::unique_ptr<application_t>(new application_t());
  }

  static std::unique_ptr<application_t> init(const int& argc,
                                             const char** argv) {
    if (initialized_) {
      throw std::runtime_error("caitlyn::init can only be called once.");
    }
    initialized_ = true;
    return std::unique_ptr<application_t>(new application_t(argc, argv));
  }

  const std::vector<std::string>& get_args() const { return args_; }

  const char* system_name() const {
#if defined(__CAITLYN_OS_LINUX)
    return "Linux";
#elif defined(__CAITLYN_OS_APPLE)
    return "Apple";
#elif defined(__CAITLYN_OS_WINDOWS)
    return "Windows";
#elif defined(__CAITLYN_OS_ANDROID)
    return "Android";
#endif
  }

private:
  application_t() { configure(); }

  application_t(const int argc, const char** argv) {
    if (argc > 0) {
      args_.reserve(argc);
      for (int i = 0; i < argc; ++i) {
        args_.emplace_back(argv[i]);
      }
    }
    configure();
  }

  static void configure() {
#ifdef __CAITLYN_OS_WINDOWS
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
  }

private:
  std::vector<std::string> args_{};
  static bool initialized_;
};

bool application_t::initialized_ = false;

__CAITLYN_DETAIL_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_APPLICATION_H_
