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

#ifndef CAITLYN_TEST_TYPES_TESTREGISTRY_H_
#define CAITLYN_TEST_TYPES_TESTREGISTRY_H_

#include <chrono>
#include <iostream>
#include <map>
#include <vector>

#include "Caitlyn/__Base.h"
#include "Caitlyn/__Testing/Types/TestCase.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TESTING_NAMESPACE_BEGIN

class TestRegistry
{
public:
    using Holder = std::map<String, std::vector<TestCase>>;
    using Counter = SizeType;
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    using Duration = std::chrono::milliseconds;

public:
    static TestRegistry& Instance()
    {
        static TestRegistry instance;
        return instance;
    }

    void AddTest(const String& suite_name, const String& test_name, const TestFunction func)
    {
        tests_[suite_name].emplace_back(suite_name, test_name, func);
        ++total_;
    }

    int RunAll()
    {
        LogStart();

        startGlobalTime_ = std::chrono::steady_clock::now();

        for (auto& suite : tests_)
        {
            LogSuiteStart(suite.first, suite.second.size());

            Duration suite_total_time{0};

            for (auto& test : suite.second)
            {
                LogTestStart(test);

                startLocalTime_ = std::chrono::steady_clock::now();
                try
                {
                    test.function();
                    test.passed = true;
                    ++passed_;
                }
                catch (const std::exception& e)
                {
                    test.passed = false;
                    LogTestFailure(test, e.what());
                    ++failed_;
                }
                catch (...)
                {
                    test.passed = false;
                    LogTestFailure(test, "Unknown error");
                    ++failed_;
                }
                stopLocalTime_ = std::chrono::steady_clock::now();
                localDiff_ =
                    std::chrono::duration_cast<std::chrono::milliseconds>(stopLocalTime_ - startLocalTime_);

                LogTestEnd(test, localDiff_);
                suite_total_time += localDiff_;
            }

            LogSuiteEnd(suite.first, suite.second.size(), suite_total_time);
        }

        stopGlobalTime_ = std::chrono::steady_clock::now();
        globalDiff_ =
            std::chrono::duration_cast<std::chrono::milliseconds>(stopGlobalTime_ - startGlobalTime_);

        LogEnd();

        skipped_ = total_ - passed_ - failed_;
        LogSummary();

        return (failed_ != 0) ? 1 : 0;
    }

private:
    TestRegistry() = default;
    ~TestRegistry() = default;

private:
    void LogStart() const
    {
        std::cout << "[==========] Running " << total_ << " tests from " << tests_.size() << " test cases.\n";
        std::cout << "[----------] Global test environment set-up.\n\n";
    }

    static void LogSuiteStart(const String& suite_name, const size_t test_count)
    {
        std::cout << "[----------] " << test_count << " tests from " << suite_name << "\n";
    }

    static void LogTestStart(const TestCase& test)
    {
        std::cout << "[ RUN      ] " << test.suite_name << '.' << test.test_name << '\n';
    }

    static void LogTestEnd(const TestCase& test, const Duration& duration)
    {
        if (test.passed)
        {
            std::cout << "[       OK ] " << test.suite_name << '.' << test.test_name << " (" << duration.count()
                      << " ms)\n";
        }
    }

    void LogTestFailure(const TestCase& test, const String& message) const
    {
        std::cout << "[     FAIL ] " << test.suite_name << '.' << test.test_name << " (" << localDiff_.count()
                  << " ms)\n"
                  << "[     INFO ] " << message << "\n";
    }

    static void LogSuiteEnd(const String& suite_name, const size_t test_count, const Duration& total_time)
    {
        std::cout << "[----------] " << test_count << " tests from " << suite_name << " (" << total_time.count()
                  << " ms total)\n\n";
    }

    void LogEnd() const
    {
        std::cout << "[----------] Global test environment tear-down\n";
        std::cout << "[==========] " << total_ << " tests from " << tests_.size() << " test cases ran. ("
                  << globalDiff_.count() << " ms total)\n";
    }

    void LogSummary() const
    {
        if (passed_ > 0)
        {
            std::cout << "[  PASSED  ] " << passed_ << " test" << (passed_ == 1 ? "" : "s") << ".\n";
        }
        if (failed_ > 0)
        {
            std::cout << "[  FAILED  ] " << failed_ << " test" << (failed_ == 1 ? "" : "s") << ", listed below:\n";
            for (const auto& suite : tests_)
            {
                for (const auto& test : suite.second)
                {
                    if (!test.passed)
                    {
                        std::cout << "[  FAILED  ] " << test.suite_name << '.' << test.test_name << '\n';
                    }
                }
            }
        }
        std::cout << '\n' << failed_ << " FAILED TEST" << (failed_ == 1 ? "" : "S") << "\n";
    }

private:
    Counter total_{};
    Counter passed_{};
    Counter failed_{};
    Counter skipped_{};
    TimePoint startGlobalTime_{};
    TimePoint stopGlobalTime_{};
    TimePoint startLocalTime_{};
    TimePoint stopLocalTime_{};
    Duration localDiff_{};
    Duration globalDiff_{};
    Holder tests_;
};

__CAITLYN_TESTING_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_TEST_TYPES_TESTREGISTRY_H_
