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

#ifndef CAITLYN_TEST_TYPES_TESTCASE_H_
#define CAITLYN_TEST_TYPES_TESTCASE_H_

#include <string>
#include <utility>

#include "Caitlyn/__Core/String.h"
#include "Caitlyn/__Testing/Types/TestFunction.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TESTING_NAMESPACE_BEGIN

struct TestCase
{
    String suite_name;
    String test_name;
    TestFunction function;
    Bool passed;

    TestCase(String suite, String name, const TestFunction func)
        : suite_name{std::move(suite)},
          test_name{std::move(name)},
          function{func},
          passed{false}
    {
    }

    ~TestCase() = default;
};

__CAITLYN_TESTING_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_TEST_TYPES_TESTCASE_H_
