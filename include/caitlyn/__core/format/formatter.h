#ifndef CAITLYN_CORE_FORMAT_FORMATTER_H_
#define CAITLYN_CORE_FORMAT_FORMATTER_H_

#include <sstream>
#include <stdexcept>
#include <vector>

#include "caitlyn/__core/format/converters.h"
#include "caitlyn/__core/format/parser.h"
#include "caitlyn/__core/format/processor.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename... Args>
basic_string_t<char> format(const basic_string_t<char>& formatter,
                            Args&&... args) {
  const std::vector<basic_string_t<char>> arguments{
      fmt::str(std::forward<Args>(args))...};

  std::ostringstream result;
  size_t auto_index = 0;
  size_t pos = 0;

  while (pos < formatter.size()) {
    if (formatter[pos] == def::left_curly_bracket) {
      if (pos + 1 < formatter.size() &&
          formatter[pos + 1] == def::left_curly_bracket) {
        result << def::left_curly_bracket;
        pos += 2;
      } else {
        const size_t end = formatter.find(def::right_curly_bracket, pos);
        if (end == basic_string_t<char>::npos) {
          throw fmt::error_t{"Mismatched braces in format string"};
        }
        const auto spec = formatter.substr(pos + 1, end - pos - 1);
        size_t arg_index = 0;
        size_t spec_pos = 0;

        if (spec.not_empty() && is_digit(spec[spec_pos])) {
          size_t index_end = spec_pos;
          while (index_end < spec.size() && is_digit(spec[index_end])) {
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
            if (format_spec[0] == def::colon) {
              auto parsed_spec = fmt::make_spec(format_spec);
              result << fmt::process(arguments[auto_index], parsed_spec);
            }
          } else {
            result << arguments[arg_index];
          }
        } else if (spec.not_empty() && spec[spec_pos] == def::colon) {
          auto parsed_spec = fmt::make_spec(spec);
          result << fmt::process(arguments[arg_index], parsed_spec);
        } else if (arguments.size() == 1) {
          result << arguments[0];
        } else if (arguments.size() > 1) {
          result << arguments[auto_index++];
        } else {
          throw fmt::error_t{"Missing argument index in format string"};
        }
        pos = end + 1;
      }
    } else if (formatter[pos] == def::right_curly_bracket) {
      if (pos + 1 < formatter.size() &&
          formatter[pos + 1] == def::right_curly_bracket) {
        result << def::right_curly_bracket;
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

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_FORMAT_FORMATTER_H_