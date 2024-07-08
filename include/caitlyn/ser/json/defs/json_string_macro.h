// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_DEFS_JSON_STRING_MACRO_H_
#define CAITLYN_SER_JSON_DEFS_JSON_STRING_MACRO_H_

#define json_str(...) cait::make_json(#__VA_ARGS__)

#define json_path(...) cait::vector_t<cait::string_t>{__VA_ARGS__}

#define json_index(index) std::to_string(index)

#endif  // CAITLYN_SER_JSON_DEFS_JSON_STRING_MACRO_H_
