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

#ifndef CAITLYN_TEST_MACRO_FIXTURE_H_
#define CAITLYN_TEST_MACRO_FIXTURE_H_

#include "caitlyn/test/types.h"

#define TEST_F(fixture, test_case_name)                           \
  struct test_case_name##_fixture : public fixture {              \
    void run();                                                   \
  };                                                              \
  namespace {                                                     \
  struct test_case_name##_registrar {                             \
    test_case_name##_registrar() {                                \
      cait::test::registry_t::instance().add_test(                \
          #fixture, #test_case_name,                              \
          []() { test_case_name##_fixture().run(); });            \
    }                                                             \
  };                                                              \
  test_case_name##_registrar test_case_name##_registrar_instance; \
  }                                                               \
  void test_case_name##_fixture::run()

#endif  // CAITLYN_TEST_MACRO_FIXTURE_H_
