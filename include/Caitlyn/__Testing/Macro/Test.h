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

#ifndef CAITLYN_TEST_MACRO_TEST_H_
#define CAITLYN_TEST_MACRO_TEST_H_

#include "Caitlyn/__Testing/Types.h"

#define TEST(TestSuiteName, TestCaseName)                                                                              \
    void TestSuiteName##_##TestCaseName();                                                                             \
    namespace                                                                                                          \
    {                                                                                                                  \
    struct TestSuiteName##_##TestCaseName##_Registrar                                                                  \
    {                                                                                                                  \
        TestSuiteName##_##TestCaseName##_Registrar()                                                                   \
        {                                                                                                              \
            Caitlyn::Test::TestRegistry::Instance().AddTest(                                                           \
                #TestSuiteName, #TestCaseName, TestSuiteName##_##TestCaseName);                                        \
        }                                                                                                              \
    };                                                                                                                 \
    TestSuiteName##_##TestCaseName##_Registrar TestSuiteName##_##TestCaseName##_Registrar_Instance;                    \
    }                                                                                                                  \
    void TestSuiteName##_##TestCaseName()

#endif // CAITLYN_TEST_MACRO_TEST_H_
