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

#ifndef CAITLYN_TEST_MACRO_ASSERT_H_
#define CAITLYN_TEST_MACRO_ASSERT_H_

#include "caitlyn/core/traits.h"
#include "caitlyn/test/types.h"

#define ASSERT_TRUE(condition) \
  if (!(condition)) throw std::runtime_error("Assertion failed: " #condition)

#define ASSERT_FALSE(condition) \
  if (condition) throw std::runtime_error("Assertion failed: " #condition)

#define ASSERT_EQ(val1, val2)                                      \
  if (!((val1) == (val2))) {                                       \
    std::ostringstream oss;                                        \
    oss << "Assertion failed: " #val1 " == " #val2 << " (" << val1 \
        << " != " << val2 << ")";                                  \
    throw std::runtime_error(oss.str());                           \
  }

#define ASSERT_NE(val1, val2)                                      \
  if (!((val1) != (val2))) {                                       \
    std::ostringstream oss;                                        \
    oss << "Assertion failed: " #val1 " != " #val2 << " (" << val1 \
        << " == " << val2 << ")";                                  \
    throw std::runtime_error(oss.str());                           \
  }

#define ASSERT_LT(val1, val2)                                     \
  if (!((val1) < (val2))) {                                       \
    std::ostringstream oss;                                       \
    oss << "Assertion failed: " #val1 " < " #val2 << " (" << val1 \
        << " >= " << val2 << ")";                                 \
    throw std::runtime_error(oss.str());                          \
  }

#define ASSERT_LE(val1, val2)                                               \
  if (!((val1) <= (val2))) {                                                \
    std::ostringstream oss;                                                 \
    oss << "Assertion failed: " #val1 " <= " #val2 << " (" << val1 << " > " \
        << val2 << ")";                                                     \
    throw std::runtime_error(oss.str());                                    \
  }

#define ASSERT_GT(val1, val2)                                     \
  if (!((val1) > (val2))) {                                       \
    std::ostringstream oss;                                       \
    oss << "Assertion failed: " #val1 " > " #val2 << " (" << val1 \
        << " <= " << val2 << ")";                                 \
    throw std::runtime_error(oss.str());                          \
  }

#define ASSERT_GE(val1, val2)                                               \
  if (!((val1) >= (val2))) {                                                \
    std::ostringstream oss;                                                 \
    oss << "Assertion failed: " #val1 " >= " #val2 << " (" << val1 << " < " \
        << val2 << ")";                                                     \
    throw std::runtime_error(oss.str());                                    \
  }

#define ASSERT_EQ_PRINTABLE(val1, val2)                                  \
  if (!((val1) == (val2))) {                                             \
    static_assert(cait::has_output_operator<decltype(val1)>::value &&    \
                      cait::has_output_operator<decltype(val2)>::value,  \
                  "Types must be printable to use ASSERT_EQ_PRINTABLE"); \
    std::ostringstream oss;                                              \
    oss << "Assertion failed: " #val1 " == " #val2 << " (" << val1       \
        << " != " << val2 << ")";                                        \
    throw std::runtime_error(oss.str());                                 \
  }

#endif  // CAITLYN_TEST_MACRO_ASSERT_H_
