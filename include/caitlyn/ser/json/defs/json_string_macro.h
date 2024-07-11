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

#ifndef CAITLYN_SER_JSON_DEFS_JSON_STRING_MACRO_H_
#define CAITLYN_SER_JSON_DEFS_JSON_STRING_MACRO_H_

#define json_str(...) cait::make_json(#__VA_ARGS__)

#endif  // CAITLYN_SER_JSON_DEFS_JSON_STRING_MACRO_H_
