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

#ifndef CAITLYN_TEST_TYPES_TESTFAILMESSAGE_H_
#define CAITLYN_TEST_TYPES_TESTFAILMESSAGE_H_

#include <sstream>

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TESTING_NAMESPACE_BEGIN

class TestFailMessage
{
public:
    TestFailMessage(const char* file, const int line) : file_{file}, line{line}
    {
    }

    template <typename T>
    TestFailMessage& operator<<(const T& value)
    {
        message << value;
        Fail();
        return *this;
    }

    void Fail() const
    {
        std::ostringstream oss;
        oss << "FAILURE: Test failed at " << file_ << ":" << line << " - " << message.str();
        throw std::runtime_error(oss.str());
    }

private:
    String file_;
    int line;
    std::ostringstream message;
};

__CAITLYN_TESTING_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_TEST_TYPES_TESTFAILMESSAGE_H_
