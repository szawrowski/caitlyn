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

#ifndef CAITLYN_TEST_TYPES_REGISTRY_H_
#define CAITLYN_TEST_TYPES_REGISTRY_H_

#include <iostream>
#include <map>
#include <vector>

#include "caitlyn/test/types/case.h"

namespace cait {
namespace test {

class registry_t {
public:
  static registry_t& instance() {
    static registry_t instance;
    return instance;
  }

  void add_test(const std::string& suite_name, const std::string& test_name,
                const function_t func) {
    tests_[suite_name].emplace_back(case_t{suite_name, test_name, func});
  }

  void run_all() const {
    int_t passed{};
    int_t failed{};
    for (const auto& suite : tests_) {
      for (const auto& test : suite.second) {
        try {
          test.function();
          std::cout << "[PASSED] " << test.suite_name << '.' << test.test_name
                    << "\n";
          ++passed;
        } catch (const std::exception& e) {
          std::cout << "[FAILED] " << test.suite_name << '.' << test.test_name
                    << ": " << e.what() << "\n";
          ++failed;
        } catch (...) {
          std::cout << "[FAILED] " << test.suite_name << '.' << test.test_name
                    << ": Unknown error\n";
          ++failed;
        }
      }
    }
    std::cout << "\nTotal tests: " << (passed + failed)
              << "\nPassed: " << passed
              << "\nFailed: " << failed << '\n';
  }

private:
  registry_t() = default;
  std::map<std::string, std::vector<case_t>> tests_;
};

}  // namespace test
}  // namespace cait

#endif  // CAITLYN_TEST_TYPES_REGISTRY_H_
