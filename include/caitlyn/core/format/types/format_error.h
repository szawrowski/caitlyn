// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_FORMAT_TYPES_FORMAT_ERROR_H_
#define CAITLYN_CORE_FORMAT_TYPES_FORMAT_ERROR_H_

#include <stdexcept>

namespace cait {
namespace strfmt {

class format_error_t final : public std::runtime_error {
public:
  explicit format_error_t(const std::string& message)
      : std::runtime_error(message) {}
};

}  // namespace strfmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_TYPES_FORMAT_ERROR_H_
