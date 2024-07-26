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

#ifndef CAITLYN_CORE_NUMERIC_TYPES_RADIX_H_
#define CAITLYN_CORE_NUMERIC_TYPES_RADIX_H_

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

enum class Radix : Byte
{
    Binary = 0x1,
    Octal = 0x7,
    Decimal = 0x9,
    Hex = 0xF,
};

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_NUMERIC_TYPES_RADIX_H_
