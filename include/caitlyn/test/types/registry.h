#ifndef CAITLYN_TEST_TYPES_REGISTRY_H_
#define CAITLYN_TEST_TYPES_REGISTRY_H_

#include <chrono>
#include <iostream>
#include <map>
#include <vector>

#include "caitlyn/__base.h"
#include "caitlyn/test/types/case.h"

namespace cait {
namespace test {

class registry_t {
public:
  using holder_type = std::map<std::string, std::vector<case_t>>;
  using counter_type = size_t;
  using time_point = std::chrono::time_point<std::chrono::steady_clock>;
  using milliseconds_type =
      std::chrono::duration<long long, std::ratio<1, 1000>>;

public:
  static registry_t& instance() {
    static registry_t instance;
    return instance;
  }

  void add_test(const std::string& suite_name, const std::string& test_name,
                const function_t func) {
    tests_[suite_name].emplace_back(suite_name, test_name, func);
    ++total_;
  }

  __caitlyn_nodiscard int run_all() {
    log_start();

    start_global_time_ = std::chrono::steady_clock::now();

    for (auto& suite : tests_) {
      log_suite_start(suite.first, suite.second.size());

      milliseconds_type suite_total_time{0};

      for (auto& test : suite.second) {
        log_test_start(test);

        start_local_time_ = std::chrono::steady_clock::now();
        try {
          test.function();
          test.passed = true;
          ++passed_;
        } catch (const std::exception& e) {
          test.passed = false;
          log_test_failure(test, e.what());
          ++failed_;
        } catch (...) {
          test.passed = false;
          log_test_failure(test, "Unknown error");
          ++failed_;
        }
        stop_local_time_ = std::chrono::steady_clock::now();
        local_difference_ =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                stop_local_time_ - start_local_time_);

        log_test_end(test, local_difference_);
        suite_total_time += local_difference_;
      }

      log_suite_end(suite.first, suite.second.size(), suite_total_time);
    }

    stop_global_time_ = std::chrono::steady_clock::now();
    global_difference_ = std::chrono::duration_cast<std::chrono::milliseconds>(
        stop_global_time_ - start_global_time_);

    log_end();

    skipped_ = total_ - passed_ - failed_;

    log_summary();

    return (failed_ != 0) ? 1 : 0;
  }

private:
  registry_t() = default;
  ~registry_t() = default;

private:
  void log_start() const {
    std::cout << "[==========] Running " << total_ << " tests from "
              << tests_.size() << " test cases.\n";
    std::cout << "[----------] Global test environment set-up.\n\n";
  }

  static void log_suite_start(const std::string& suite_name,
                              const size_t test_count) {
    std::cout << "[----------] " << test_count << " tests from " << suite_name
              << "\n";
  }

  static void log_test_start(const case_t& test) {
    std::cout << "[ RUN      ] " << test.suite_name << '.' << test.test_name
              << '\n';
  }

  static void log_test_end(const case_t& test,
                           const milliseconds_type& duration) {
    if (test.passed) {
      std::cout << "[       OK ] " << test.suite_name << '.' << test.test_name
                << " (" << duration.count() << " ms)\n";
    }
  }

  void log_test_failure(const case_t& test, const std::string& message) const {
    std::cout << "[     FAIL ] " << test.suite_name << '.' << test.test_name
              << " (" << local_difference_.count() << " ms)\n"
              << "[     INFO ] " << message << "\n";
  }

  static void log_suite_end(const std::string& suite_name,
                            const size_t test_count,
                            const milliseconds_type& total_time) {
    std::cout << "[----------] " << test_count << " tests from " << suite_name
              << " (" << total_time.count() << " ms total)\n\n";
  }

  void log_end() const {
    std::cout << "[----------] Global test environment tear-down\n";
    std::cout << "[==========] " << total_ << " tests from " << tests_.size()
              << " test cases ran. (" << global_difference_.count()
              << " ms total)\n";
  }

  void log_summary() const {
    if (passed_ > 0) {
      std::cout << "[  PASSED  ] " << passed_ << " test"
                << (passed_ == 1 ? "" : "s") << ".\n";
    }
    if (failed_ > 0) {
      std::cout << "[  FAILED  ] " << failed_ << " test"
                << (failed_ == 1 ? "" : "s") << ", listed below:\n";
      for (const auto& suite : tests_) {
        for (const auto& test : suite.second) {
          if (!test.passed) {
            std::cout << "[  FAILED  ] " << test.suite_name << '.'
                      << test.test_name << '\n';
          }
        }
      }
    }
    std::cout << '\n'
              << failed_ << " FAILED TEST" << (failed_ == 1 ? "" : "S") << "\n";
  }

private:
  counter_type total_{};
  counter_type passed_{};
  counter_type failed_{};
  counter_type skipped_{};

  time_point start_global_time_{};
  time_point stop_global_time_{};
  time_point start_local_time_{};
  time_point stop_local_time_{};

  milliseconds_type local_difference_{};
  milliseconds_type global_difference_{};

  holder_type tests_;
};

}  // namespace test
}  // namespace cait

#endif  // CAITLYN_TEST_TYPES_REGISTRY_H_
