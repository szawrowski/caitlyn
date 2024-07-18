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
constexpr auto colon = ":";

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
        // Extracting the contents of {}
        const auto spec = formatter.substr(pos + 1, end - pos - 1);

        if (spec.not_empty()) {
          constexpr size_t spec_begin = 0;
          size_t format_spec_begin = 0;
          size_t arg_index = 0;
          bool has_index = false;
          string_t format_spec;

          // Parsing the index, if it exists {}
          if (fmt::is_digit(spec[spec_begin])) {
            format_spec_begin = spec_begin;

            while (format_spec_begin < spec.size() &&
                   fmt::is_digit(spec[format_spec_begin])) {
              ++format_spec_begin;
            }
            try {
              arg_index = std::stoul(
                  spec.substr(spec_begin, format_spec_begin - spec_begin)
                      .str());
            } catch (const std::out_of_range&) {
              throw fmt::error_t{"Invalid argument index"};
            }
            if (arg_index > arguments.size() - 1) {
              throw fmt::error_t{"Argument index out of range"};
            }
            format_spec = spec.substr(format_spec_begin);
            has_index = true;
          } else {
            format_spec = spec;
            has_index = false;
          }

          if (format_spec.not_empty()) {
            if (format_spec[0] != fmt::colon) {
              throw fmt::error_t{"Invalid format specifier. Expected colon"};
            }
            auto parsed_spec = fmt::make_spec(format_spec);

            if (has_index) {
              result << fmt::process(arguments[arg_index], parsed_spec);
            } else {
              if (arguments.size() == 1) {
                result << fmt::process(arguments[0], parsed_spec);
              } else if (arguments.size() > 1) {
                if (auto_index > arguments.size() - 1) {
                  throw fmt::error_t{"Argument index out of range"};
                }
                result << fmt::process(arguments[auto_index++], parsed_spec);
              }
            }
          } else {
            if (arguments.size() == 1) {
              result << arguments[0];
            } else if (arguments.size() > 1) {
              if (auto_index > arguments.size() - 1) {
                throw fmt::error_t{"Argument index out of range"};
              }
              result << arguments[auto_index++];
            }
          }
        } else {
          if (arguments.size() == 1) {
            result << arguments[0];
          } else if (arguments.size() > 1) {
            if (auto_index > arguments.size() - 1) {
              throw fmt::error_t{"Argument index out of range"};
            }
            result << arguments[auto_index++];
          }
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

inline string_t format(const string_t& formatter) {
  return format(formatter, "");
}

}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_FORMATTER_H_
