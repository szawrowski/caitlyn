#ifndef CAITLYN_CORE_FORMAT_FORMATTER_H_
#define CAITLYN_CORE_FORMAT_FORMATTER_H_

#include <sstream>
#include <stdexcept>
#include <vector>

#include "caitlyn/core/format/processor.h"

namespace cait {
namespace fmt {

constexpr auto left_curly_bracket = "{";
constexpr auto right_curly_bracket = "}";

}  // namespace fmt

template <typename... Args>
string_t format(const string_t& formatter, Args&&... args) {
  const std::vector<string_t> arguments{fmt::str(std::forward<Args>(args))...};

  std::ostringstream result;
  size_t auto_index = 0;
  size_t pos = 0;

  while (pos < formatter.size()) {
    if (formatter[pos] == fmt::left_curly_bracket) {
      if (pos + 1 < formatter.size() &&
          formatter[pos + 1] == fmt::left_curly_bracket) {
        result << fmt::left_curly_bracket;
        pos += 2;
      } else {
        const size_t end = formatter.find(fmt::right_curly_bracket, pos);
        if (end == string_t::npos) {
          throw fmt::error_t{"Mismatched braces in format string"};
        }
        const auto spec = formatter.substr(pos + 1, end - pos - 1);
        size_t arg_index = 0;
        size_t spec_pos = 0;

        if (!spec.is_empty() && fmt::is_digit(spec[spec_pos])) {
          size_t index_end = spec_pos;
          while (index_end < spec.size() && fmt::is_digit(spec[index_end])) {
            ++index_end;
          }
          try {
            arg_index =
                std::stoul(spec.substr(spec_pos, index_end - spec_pos).str());
          } catch (const std::out_of_range&) {
            throw fmt::error_t{"Invalid argument index"};
          }
          if (arg_index > arguments.size() - 1) {
            throw fmt::error_t{"Argument index out of range"};
          }
          auto format_spec = spec.substr(index_end);
          if (!format_spec.is_empty()) {
            if (format_spec[0] == ":") {
              auto parsed_spec = fmt::make_spec(format_spec);

              if (parsed_spec.type == fmt::type_t::integral) {
                result << fmt::process_integral(arguments[arg_index],
                                                parsed_spec);
              } else if (parsed_spec.type == fmt::type_t::floating) {
                result << fmt::process_floating(arguments[arg_index],
                                                parsed_spec);
              } else {
                result << fmt::process_string(arguments[arg_index],
                                              parsed_spec);
              }
            }
          } else {
            result << arguments[arg_index];
          }
        } else if (arguments.size() == 1) {
          result << arguments[0];
        } else if (arguments.size() > 1) {
          result << arguments[auto_index++];
        } else {
          throw fmt::error_t{"Missing argument index in format string"};
        }
        pos = end + 1;
      }
    } else if (formatter[pos] == fmt::right_curly_bracket) {
      if (pos + 1 < formatter.size() &&
          formatter[pos + 1] == fmt::right_curly_bracket) {
        result << fmt::right_curly_bracket;
        pos += 2;
      } else {
        throw fmt::error_t{"Single right curly bracket in format string"};
      }
    } else {
      result << formatter[pos++];
    }
  }
  return result.str();
}

}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_FORMATTER_H_
