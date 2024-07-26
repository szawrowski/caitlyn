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

#ifndef CAITLYN_SERIALIZING_JSON_TYPES_CLASS_H_
#define CAITLYN_SERIALIZING_JSON_TYPES_CLASS_H_

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_JSON_NAMESPACE_BEGIN

enum class JsonClass
{
    Null,
    Object,
    Array,
    String,
    Floating,
    Integral,
    Boolean
};

__CAITLYN_JSON_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_SERIALIZING_JSON_TYPES_CLASS_H_
