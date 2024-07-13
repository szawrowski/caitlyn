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

#ifndef CAITLYN_TEST_TYPES_FAIL_MESSAGE_H_
#define CAITLYN_TEST_TYPES_FAIL_MESSAGE_H_

#include <sstream>

#include "caitlyn/base.h"

namespace cait {
namespace test {

class fail_message_t {
public:
  fail_message_t(const char_t* file, const int_t line) : file{file}, line{line} {}

  template <typename T>
  fail_message_t& operator<<(const T& value) {
    message << value;
    fail();
    return *this;
  }

  void fail() const {
    std::ostringstream oss;
    oss << "FAILURE: Test failed at " << file << ":" << line << " - "
        << message.str();
    throw std::runtime_error(oss.str());
  }

private:
  const char_t* file;
  int_t line;
  std::ostringstream message;
};

}  // namespace test
}  // namespace cait

#endif  // CAITLYN_TEST_TYPES_FAIL_MESSAGE_H_
