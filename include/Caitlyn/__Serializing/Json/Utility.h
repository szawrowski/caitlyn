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

#ifndef CAITLYN_SERIALIZING_JSON_UTILITY_H_
#define CAITLYN_SERIALIZING_JSON_UTILITY_H_

#include <string>

#include "Caitlyn/__Serializing/Json/Types/JsonError.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_JSON_NAMESPACE_BEGIN

inline const char* GetErrorString(const JsonError error)
{
    switch (error)
    {
        case JsonError::NoError:
            return "No error.";
        case JsonError::UnterminatedString:
            return "Unterminated string.";
        case JsonError::ExpectedStringKey:
            return "Expected string key.";
        case JsonError::MissingColon:
            return "Missing colon.";
        case JsonError::UnterminatedObject:
            return "Unterminated object.";
        case JsonError::UnterminatedArray:
            return "Unterminated array.";
        case JsonError::InvalidNumber:
            return "Invalid number.";
        case JsonError::NumberConversionError:
            return "Number conversion error.";
        case JsonError::InvalidValue:
            return "Invalid value.";
        case JsonError::UnexpectedCharacter:
            return "Unexpected character.";
        case JsonError::TrailingComma:
            return "Trailing comma.";
        case JsonError::InvalidJson:
            return "Invalid JSON.";
        default:
            return "Unknown error.";
    }
}

__CAITLYN_JSON_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_SERIALIZING_JSON_UTILITY_H_
