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

#ifndef CAITLYN_CORE_MEMORY_UTILITY_SIZECALCULATION_H_
#define CAITLYN_CORE_MEMORY_UTILITY_SIZECALCULATION_H_

#include "Caitlyn/__Core/Memory/Types/MemoryFormat.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
constexpr SizeType SizeOf(const MemoryFormat mf = MemoryFormat::Byte)
{
    return mf == MemoryFormat::Byte ? sizeof(T) : sizeof(T) * 8;
}

template <typename T>
constexpr SizeType SizeOf(const T& value, const MemoryFormat mf = MemoryFormat::Byte)
{
    return mf == MemoryFormat::Byte ? sizeof(value) : sizeof(value) * 8;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_MEMORY_UTILITY_SIZECALCULATION_H_
