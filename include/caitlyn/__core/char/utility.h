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

#ifndef CAITLYN_CORE_CHAR_UTILITY_H_
#define CAITLYN_CORE_CHAR_UTILITY_H_

#include <unordered_map>
#include <unordered_set>

#include "caitlyn/__core/char/types/codepoint.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

inline bool is_space(const codepoint_t codepoint)
{
    static const std::unordered_set<codepoint_t> space_codepoints{
        codepoint_t{0x0009}, // CHARACTER TABULATION
        codepoint_t{0x000A}, // LINE FEED
        codepoint_t{0x000B}, // LINE TABULATION
        codepoint_t{0x000C}, // FORM FEED
        codepoint_t{0x000D}, // CARRIAGE RETURN
        codepoint_t{0x0020}, // SPACE
        codepoint_t{0x0085}, // NEXT LINE
        codepoint_t{0x00A0}, // NO-BREAK SPACE
        codepoint_t{0x1680}, // OGHAM SPACE MARK
        codepoint_t{0x2000}, // EN QUAD
        codepoint_t{0x2001}, // EM QUAD
        codepoint_t{0x2002}, // EN SPACE
        codepoint_t{0x2003}, // EM SPACE
        codepoint_t{0x2004}, // THREE-PER-EM SPACE
        codepoint_t{0x2005}, // FOUR-PER-EM SPACE
        codepoint_t{0x2006}, // SIX-PER-EM SPACE
        codepoint_t{0x2007}, // FIGURE SPACE
        codepoint_t{0x2008}, // PUNCTUATION SPACE
        codepoint_t{0x2009}, // THIN SPACE
        codepoint_t{0x200A}, // HAIR SPACE
        codepoint_t{0x2028}, // LINE SEPARATOR
        codepoint_t{0x2029}, // PARAGRAPH SEPARATOR
        codepoint_t{0x202F}, // NARROW NO-BREAK SPACE
        codepoint_t{0x205F}, // MEDIUM MATHEMATICAL SPACE
        codepoint_t{0x3000}  // IDEOGRAPHIC SPACE
    };
    return space_codepoints.find(codepoint) != space_codepoints.end();
}

inline bool is_digit(const uint32_t codepoint)
{
    const auto digit =
        // DIGIT ZERO - DIGIT NINE
        (codepoint >= 0x0030 && codepoint <= 0x0039) ||
        // ARABIC-INDIC DIGIT ZERO - ARABIC-INDIC DIGIT NINE
        (codepoint >= 0x0660 && codepoint <= 0x0669) ||
        // EXTENDED ARABIC-INDIC DIGIT ZERO - EXTENDED ARABIC-INDIC DIGIT NINE
        (codepoint >= 0x06F0 && codepoint <= 0x06F9) ||
        // NKO DIGIT ZERO - NKO DIGIT NINE
        (codepoint >= 0x07C0 && codepoint <= 0x07C9) ||
        // DEVANAGARI DIGIT ZERO - DEVANAGARI DIGIT NINE
        (codepoint >= 0x0966 && codepoint <= 0x096F) ||
        // BENGALI DIGIT ZERO - BENGALI DIGIT NINE
        (codepoint >= 0x09E6 && codepoint <= 0x09EF) ||
        // GURMUKHI DIGIT ZERO - GURMUKHI DIGIT NINE
        (codepoint >= 0x0A66 && codepoint <= 0x0A6F) ||
        // GUJARATI DIGIT ZERO - GUJARATI DIGIT NINE
        (codepoint >= 0x0AE6 && codepoint <= 0x0AEF) ||
        // ORIYA DIGIT ZERO - ORIYA DIGIT NINE
        (codepoint >= 0x0B66 && codepoint <= 0x0B6F) ||
        // TAMIL DIGIT ZERO - TAMIL DIGIT NINE
        (codepoint >= 0x0BE6 && codepoint <= 0x0BEF) ||
        // TELUGU DIGIT ZERO - TELUGU DIGIT NINE
        (codepoint >= 0x0C66 && codepoint <= 0x0C6F) ||
        // KANNADA DIGIT ZERO - KANNADA DIGIT NINE
        (codepoint >= 0x0CE6 && codepoint <= 0x0CEF) ||
        // MALAYALAM DIGIT ZERO - MALAYALAM DIGIT NINE
        (codepoint >= 0x0D66 && codepoint <= 0x0D6F) ||
        // THAI DIGIT ZERO - THAI DIGIT NINE
        (codepoint >= 0x0E50 && codepoint <= 0x0E59) ||
        // LAO DIGIT ZERO - LAO DIGIT NINE
        (codepoint >= 0x0ED0 && codepoint <= 0x0ED9) ||
        // TIBETAN DIGIT ZERO - TIBETAN DIGIT NINE
        (codepoint >= 0x0F20 && codepoint <= 0x0F29) ||
        // MYANMAR DIGIT ZERO - MYANMAR DIGIT NINE
        (codepoint >= 0x1040 && codepoint <= 0x1049) ||
        // MYANMAR SHAN DIGIT ZERO - MYANMAR SHAN DIGIT NINE
        (codepoint >= 0x1090 && codepoint <= 0x1099) ||
        // KHMER DIGIT ZERO - KHMER DIGIT NINE
        (codepoint >= 0x17E0 && codepoint <= 0x17E9) ||
        // MONGOLIAN DIGIT ZERO - MONGOLIAN DIGIT NINE
        (codepoint >= 0x1810 && codepoint <= 0x1819) ||
        // LIMBU DIGIT ZERO - LIMBU DIGIT NINE
        (codepoint >= 0x1946 && codepoint <= 0x194F) ||
        // NEW TAI LUE DIGIT ZERO - NEW TAI LUE DIGIT NINE
        (codepoint >= 0x19D0 && codepoint <= 0x19D9) ||
        // TAI THAM HORA DIGIT ZERO - TAI THAM HORA DIGIT NINE
        (codepoint >= 0x1A80 && codepoint <= 0x1A89) ||
        // TAI THAM THAM DIGIT ZERO - TAI THAM THAM DIGIT NINE
        (codepoint >= 0x1A90 && codepoint <= 0x1A99) ||
        // BALINESE DIGIT ZERO - BALINESE DIGIT NINE
        (codepoint >= 0x1B50 && codepoint <= 0x1B59) ||
        // SUNDANESE DIGIT ZERO - SUNDANESE DIGIT NINE
        (codepoint >= 0x1BB0 && codepoint <= 0x1BB9) ||
        // LEPCHA DIGIT ZERO - LEPCHA DIGIT NINE
        (codepoint >= 0x1C40 && codepoint <= 0x1C49) ||
        // OL CHIKI DIGIT ZERO - OL CHIKI DIGIT NINE
        (codepoint >= 0x1C50 && codepoint <= 0x1C59) ||
        // VAI DIGIT ZERO - VAI DIGIT NINE
        (codepoint >= 0xA620 && codepoint <= 0xA629) ||
        // SAURASHTRA DIGIT ZERO - SAURASHTRA DIGIT NINE
        (codepoint >= 0xA8D0 && codepoint <= 0xA8D9) ||
        // KAYAH LI DIGIT ZERO - KAYAH LI DIGIT NINE
        (codepoint >= 0xA900 && codepoint <= 0xA909) ||
        // JAVANESE DIGIT ZERO - JAVANESE DIGIT NINE
        (codepoint >= 0xA9D0 && codepoint <= 0xA9D9) ||
        // MYANMAR TAI LAING DIGIT ZERO - MYANMAR TAI LAING DIGIT NINE
        (codepoint >= 0xA9F0 && codepoint <= 0xA9F9) ||
        // CHAM DIGIT ZERO - CHAM DIGIT NINE
        (codepoint >= 0xAA50 && codepoint <= 0xAA59) ||
        // MEETEI MAYEK DIGIT ZERO - MEETEI MAYEK DIGIT NINE
        (codepoint >= 0xABF0 && codepoint <= 0xABF9) ||
        // FULLWIDTH DIGIT ZERO - FULLWIDTH DIGIT NINE
        (codepoint >= 0xFF10 && codepoint <= 0xFF19);

    return digit;
}

inline codepoint_t to_uppercase(const codepoint_t codepoint)
{
    const std::unordered_map<codepoint_t, codepoint_t> special_case_upper{
        {codepoint_t{0x00DF}, codepoint_t{0x1E9E}}, // ß -> ẞ
        {codepoint_t{0x0131}, codepoint_t{0x0049}}, // ı -> I
        {codepoint_t{0x0149}, codepoint_t{0x02BC}}  // ŉ -> ’n
    };
    if (special_case_upper.find(codepoint) != special_case_upper.end())
    {
        return special_case_upper.at(codepoint);
    }
    // Latin
    if (codepoint >= 0x61 && codepoint <= 0x7A)
    {
        return codepoint - 0x20;
    }
    // Cirillic
    if (codepoint >= 0x430 && codepoint <= 0x44F)
    {
        return codepoint - 0x20;
    }
    // Greek
    if (codepoint >= 0x3B1 && codepoint <= 0x3C1)
    {
        return codepoint - 0x20;
    }
    if (codepoint >= 0x3C3 && codepoint <= 0x3C9)
    {
        return codepoint - 0x20;
    }
    // Additional
    if (codepoint >= 0x1F00 && codepoint <= 0x1F07)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F10 && codepoint <= 0x1F15)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F20 && codepoint <= 0x1F27)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F30 && codepoint <= 0x1F37)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F40 && codepoint <= 0x1F45)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F60 && codepoint <= 0x1F67)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F70 && codepoint <= 0x1F71)
    {
        return codepoint + 0x56;
    }
    if (codepoint >= 0x1F72 && codepoint <= 0x1F75)
    {
        return codepoint + 0x64;
    }
    if (codepoint >= 0x1F76 && codepoint <= 0x1F77)
    {
        return codepoint + 0x80;
    }
    if (codepoint >= 0x1F78 && codepoint <= 0x1F79)
    {
        return codepoint + 0x7E;
    }
    if (codepoint >= 0x1F7A && codepoint <= 0x1F7B)
    {
        return codepoint + 0x7C;
    }
    if (codepoint >= 0x1F7C && codepoint <= 0x1F7D)
    {
        return codepoint + 0x7A;
    }
    // Ranges for Latin characters with diacritics
    if (codepoint >= 0x0100 && codepoint <= 0x012F)
    {
        if (codepoint % 2 == 0)
        {
            return codepoint;
        }
        return codepoint - 1;
    }
    if (codepoint >= 0x0132 && codepoint <= 0x0137)
    {
        if (codepoint % 2 == 0)
        {
            return codepoint;
        }
        return codepoint - 1;
    }
    if (codepoint >= 0x0139 && codepoint <= 0x0148)
    {
        if (codepoint % 2 == 0)
        {
            return codepoint;
        }
        return codepoint - 1;
    }
    if (codepoint >= 0x014A && codepoint <= 0x0177)
    {
        if (codepoint % 2 == 0)
        {
            return codepoint;
        }
        return codepoint - 1;
    }
    return codepoint;
}

inline codepoint_t to_lowercase(const codepoint_t codepoint)
{
    const std::unordered_map<codepoint_t, codepoint_t> special_case_lower{
        {codepoint_t{0x1E9E}, codepoint_t{0x00DF}}, // ẞ -> ß
        {codepoint_t{0x0130}, codepoint_t{0x0069}}, // İ -> i
        {codepoint_t{0x212A}, codepoint_t{0x006B}}, // K -> k
        {codepoint_t{0x212B}, codepoint_t{0x00E5}}  // Å -> å
    };
    if (special_case_lower.find(codepoint) != special_case_lower.end())
    {
        return special_case_lower.at(codepoint);
    }
    // Latin
    if (codepoint >= 0x41 && codepoint <= 0x5A)
    {
        return codepoint + 0x20;
    }
    // Cirillic
    if (codepoint >= 0x410 && codepoint <= 0x42F)
    {
        return codepoint + 0x20;
    }
    // Greek
    if (codepoint >= 0x391 && codepoint <= 0x3A1)
    {
        return codepoint + 0x20;
    }
    if (codepoint >= 0x3A3 && codepoint <= 0x3A9)
    {
        return codepoint + 0x20;
    }
    // Aditional
    if (codepoint >= 0x1F08 && codepoint <= 0x1F0F)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F18 && codepoint <= 0x1F1D)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F28 && codepoint <= 0x1F2F)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F38 && codepoint <= 0x1F3F)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F48 && codepoint <= 0x1F4D)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1F68 && codepoint <= 0x1F6F)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1FB8 && codepoint <= 0x1FB9)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1FBA && codepoint <= 0x1FBB)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1FC8 && codepoint <= 0x1FCB)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1FD8 && codepoint <= 0x1FD9)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1FE8 && codepoint <= 0x1FE9)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1FEA && codepoint <= 0x1FEB)
    {
        return codepoint - 0x08;
    }
    if (codepoint >= 0x1FEC)
    {
        return codepoint - 0x08;
    }
    // Ranges for Latin characters with diacritics
    if (codepoint >= 0x0100 && codepoint <= 0x012F)
    {
        if (codepoint % 2 != 0)
        {
            return codepoint;
        }
        return codepoint + 1;
    }
    if (codepoint >= 0x0132 && codepoint <= 0x0137)
    {
        if (codepoint % 2 != 0)
        {
            return codepoint;
        }
        return codepoint + 1;
    }
    if (codepoint >= 0x0139 && codepoint <= 0x0148)
    {
        if (codepoint % 2 != 0)
        {
            return codepoint;
        }
        return codepoint + 1;
    }
    if (codepoint >= 0x014A && codepoint <= 0x0177)
    {
        if (codepoint % 2 != 0)
        {
            return codepoint;
        }
        return codepoint + 1;
    }
    return codepoint;
}

inline basic_character_t<char> to_uppercase(const basic_character_t<char>& value)
{
    return to_uppercase(value.get_codepoint());
}

inline basic_character_t<char> to_lowercase(const basic_character_t<char>& value)
{
    return to_lowercase(value.get_codepoint());
}

inline bool is_uppercase(const uint32_t codepoint)
{
    static const std::unordered_set<uint32_t> special_uppercase{
        codepoint_t{0x1E9E}, // ẞ
        codepoint_t{0x0130}, // İ
        codepoint_t{0x212A}, // K
        codepoint_t{0x212B}  // Å
    };
    if (special_uppercase.find(codepoint) != special_uppercase.end())
    {
        return true;
    }
    // Latin
    if (codepoint >= 0x41 && codepoint <= 0x5A)
    {
        return true;
    }
    // Cirillic
    if (codepoint >= 0x410 && codepoint <= 0x42F)
    {
        return true;
    }
    // Greek
    if (codepoint >= 0x391 && codepoint <= 0x3A1)
    {
        return true;
    }
    if (codepoint >= 0x3A3 && codepoint <= 0x3A9)
    {
        return true;
    }
    // Other ranges
    if (codepoint >= 0x1F08 && codepoint <= 0x1F0F)
    {
        return true;
    }
    if (codepoint >= 0x1F18 && codepoint <= 0x1F1D)
    {
        return true;
    }
    if (codepoint >= 0x1F28 && codepoint <= 0x1F2F)
    {
        return true;
    }
    if (codepoint >= 0x1F38 && codepoint <= 0x1F3F)
    {
        return true;
    }
    if (codepoint >= 0x1F48 && codepoint <= 0x1F4D)
    {
        return true;
    }
    if (codepoint >= 0x1F68 && codepoint <= 0x1F6F)
    {
        return true;
    }
    if (codepoint >= 0x1FB8 && codepoint <= 0x1FBB)
    {
        return true;
    }
    if (codepoint >= 0x1FC8 && codepoint <= 0x1FCB)
    {
        return true;
    }
    if (codepoint >= 0x1FD8 && codepoint <= 0x1FDB)
    {
        return true;
    }
    if (codepoint >= 0x1FE8 && codepoint <= 0x1FEC)
    {
        return true;
    }
    return false;
}

inline bool is_lowercase(const codepoint_t codepoint)
{
    static const std::unordered_set<uint32_t> special_lowercase{
        codepoint_t{0x00DF}, // ß
        codepoint_t{0x0131}, // ı
        codepoint_t{0x0149}  // ŉ
    };
    if (special_lowercase.find(codepoint) != special_lowercase.end())
    {
        return true;
    }
    // Latin
    if (codepoint >= 0x61 && codepoint <= 0x7A)
    {
        return true;
    }
    // Cirillic
    if (codepoint >= 0x430 && codepoint <= 0x44F)
    {
        return true;
    }
    // Greek
    if (codepoint >= 0x3B1 && codepoint <= 0x3C1)
    {
        return true;
    }
    if (codepoint >= 0x3C3 && codepoint <= 0x3C9)
    {
        return true;
    }
    // Other
    if (codepoint >= 0x1F00 && codepoint <= 0x1F07)
    {
        return true;
    }
    if (codepoint >= 0x1F10 && codepoint <= 0x1F15)
    {
        return true;
    }
    if (codepoint >= 0x1F20 && codepoint <= 0x1F27)
    {
        return true;
    }
    if (codepoint >= 0x1F30 && codepoint <= 0x1F37)
    {
        return true;
    }
    if (codepoint >= 0x1F40 && codepoint <= 0x1F45)
    {
        return true;
    }
    if (codepoint >= 0x1F60 && codepoint <= 0x1F67)
    {
        return true;
    }
    if (codepoint >= 0x1F70 && codepoint <= 0x1F7D)
    {
        return true;
    }
    return false;
}

inline bool is_alpha(const codepoint_t codepoint)
{
    return is_uppercase(codepoint) || is_lowercase(codepoint);
}

inline int to_digit(const codepoint_t codepoint)
{
    if (codepoint >= 0x30 && codepoint <= 0x39)
    {
        return static_cast<int>(codepoint) - 0x30;
    }
    return -1;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_CHAR_UTILITY_H_
