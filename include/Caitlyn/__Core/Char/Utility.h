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

#include "Caitlyn/__Core/Char/Char.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

inline bool IsSpace(const CodePoint codePoint)
{
    static const std::unordered_set<CodePoint> SpaceCodepoints{
        CodePoint{0x0009}, // CHARACTER TABULATION
        CodePoint{0x000A}, // LINE FEED
        CodePoint{0x000B}, // LINE TABULATION
        CodePoint{0x000C}, // FORM FEED
        CodePoint{0x000D}, // CARRIAGE RETURN
        CodePoint{0x0020}, // SPACE
        CodePoint{0x0085}, // NEXT LINE
        CodePoint{0x00A0}, // NO-BREAK SPACE
        CodePoint{0x1680}, // OGHAM SPACE MARK
        CodePoint{0x2000}, // EN QUAD
        CodePoint{0x2001}, // EM QUAD
        CodePoint{0x2002}, // EN SPACE
        CodePoint{0x2003}, // EM SPACE
        CodePoint{0x2004}, // THREE-PER-EM SPACE
        CodePoint{0x2005}, // FOUR-PER-EM SPACE
        CodePoint{0x2006}, // SIX-PER-EM SPACE
        CodePoint{0x2007}, // FIGURE SPACE
        CodePoint{0x2008}, // PUNCTUATION SPACE
        CodePoint{0x2009}, // THIN SPACE
        CodePoint{0x200A}, // HAIR SPACE
        CodePoint{0x2028}, // LINE SEPARATOR
        CodePoint{0x2029}, // PARAGRAPH SEPARATOR
        CodePoint{0x202F}, // NARROW NO-BREAK SPACE
        CodePoint{0x205F}, // MEDIUM MATHEMATICAL SPACE
        CodePoint{0x3000}  // IDEOGRAPHIC SPACE
    };
    return SpaceCodepoints.find(codePoint) != SpaceCodepoints.end();
}

inline bool IsDigit(const CodePoint codePoint)
{
    return
        // DIGIT ZERO - DIGIT NINE
        (codePoint >= 0x0030 && codePoint <= 0x0039) ||
        // ARABIC-INDIC DIGIT ZERO - ARABIC-INDIC DIGIT NINE
        (codePoint >= 0x0660 && codePoint <= 0x0669) ||
        // EXTENDED ARABIC-INDIC DIGIT ZERO - EXTENDED ARABIC-INDIC DIGIT NINE
        (codePoint >= 0x06F0 && codePoint <= 0x06F9) ||
        // NKO DIGIT ZERO - NKO DIGIT NINE
        (codePoint >= 0x07C0 && codePoint <= 0x07C9) ||
        // DEVANAGARI DIGIT ZERO - DEVANAGARI DIGIT NINE
        (codePoint >= 0x0966 && codePoint <= 0x096F) ||
        // BENGALI DIGIT ZERO - BENGALI DIGIT NINE
        (codePoint >= 0x09E6 && codePoint <= 0x09EF) ||
        // GURMUKHI DIGIT ZERO - GURMUKHI DIGIT NINE
        (codePoint >= 0x0A66 && codePoint <= 0x0A6F) ||
        // GUJARATI DIGIT ZERO - GUJARATI DIGIT NINE
        (codePoint >= 0x0AE6 && codePoint <= 0x0AEF) ||
        // ORIYA DIGIT ZERO - ORIYA DIGIT NINE
        (codePoint >= 0x0B66 && codePoint <= 0x0B6F) ||
        // TAMIL DIGIT ZERO - TAMIL DIGIT NINE
        (codePoint >= 0x0BE6 && codePoint <= 0x0BEF) ||
        // TELUGU DIGIT ZERO - TELUGU DIGIT NINE
        (codePoint >= 0x0C66 && codePoint <= 0x0C6F) ||
        // KANNADA DIGIT ZERO - KANNADA DIGIT NINE
        (codePoint >= 0x0CE6 && codePoint <= 0x0CEF) ||
        // MALAYALAM DIGIT ZERO - MALAYALAM DIGIT NINE
        (codePoint >= 0x0D66 && codePoint <= 0x0D6F) ||
        // THAI DIGIT ZERO - THAI DIGIT NINE
        (codePoint >= 0x0E50 && codePoint <= 0x0E59) ||
        // LAO DIGIT ZERO - LAO DIGIT NINE
        (codePoint >= 0x0ED0 && codePoint <= 0x0ED9) ||
        // TIBETAN DIGIT ZERO - TIBETAN DIGIT NINE
        (codePoint >= 0x0F20 && codePoint <= 0x0F29) ||
        // MYANMAR DIGIT ZERO - MYANMAR DIGIT NINE
        (codePoint >= 0x1040 && codePoint <= 0x1049) ||
        // MYANMAR SHAN DIGIT ZERO - MYANMAR SHAN DIGIT NINE
        (codePoint >= 0x1090 && codePoint <= 0x1099) ||
        // KHMER DIGIT ZERO - KHMER DIGIT NINE
        (codePoint >= 0x17E0 && codePoint <= 0x17E9) ||
        // MONGOLIAN DIGIT ZERO - MONGOLIAN DIGIT NINE
        (codePoint >= 0x1810 && codePoint <= 0x1819) ||
        // LIMBU DIGIT ZERO - LIMBU DIGIT NINE
        (codePoint >= 0x1946 && codePoint <= 0x194F) ||
        // NEW TAI LUE DIGIT ZERO - NEW TAI LUE DIGIT NINE
        (codePoint >= 0x19D0 && codePoint <= 0x19D9) ||
        // TAI THAM HORA DIGIT ZERO - TAI THAM HORA DIGIT NINE
        (codePoint >= 0x1A80 && codePoint <= 0x1A89) ||
        // TAI THAM THAM DIGIT ZERO - TAI THAM THAM DIGIT NINE
        (codePoint >= 0x1A90 && codePoint <= 0x1A99) ||
        // BALINESE DIGIT ZERO - BALINESE DIGIT NINE
        (codePoint >= 0x1B50 && codePoint <= 0x1B59) ||
        // SUNDANESE DIGIT ZERO - SUNDANESE DIGIT NINE
        (codePoint >= 0x1BB0 && codePoint <= 0x1BB9) ||
        // LEPCHA DIGIT ZERO - LEPCHA DIGIT NINE
        (codePoint >= 0x1C40 && codePoint <= 0x1C49) ||
        // OL CHIKI DIGIT ZERO - OL CHIKI DIGIT NINE
        (codePoint >= 0x1C50 && codePoint <= 0x1C59) ||
        // VAI DIGIT ZERO - VAI DIGIT NINE
        (codePoint >= 0xA620 && codePoint <= 0xA629) ||
        // SAURASHTRA DIGIT ZERO - SAURASHTRA DIGIT NINE
        (codePoint >= 0xA8D0 && codePoint <= 0xA8D9) ||
        // KAYAH LI DIGIT ZERO - KAYAH LI DIGIT NINE
        (codePoint >= 0xA900 && codePoint <= 0xA909) ||
        // JAVANESE DIGIT ZERO - JAVANESE DIGIT NINE
        (codePoint >= 0xA9D0 && codePoint <= 0xA9D9) ||
        // MYANMAR TAI LAING DIGIT ZERO - MYANMAR TAI LAING DIGIT NINE
        (codePoint >= 0xA9F0 && codePoint <= 0xA9F9) ||
        // CHAM DIGIT ZERO - CHAM DIGIT NINE
        (codePoint >= 0xAA50 && codePoint <= 0xAA59) ||
        // MEETEI MAYEK DIGIT ZERO - MEETEI MAYEK DIGIT NINE
        (codePoint >= 0xABF0 && codePoint <= 0xABF9) ||
        // FULLWIDTH DIGIT ZERO - FULLWIDTH DIGIT NINE
        (codePoint >= 0xFF10 && codePoint <= 0xFF19);
}

inline CodePoint ToUppercase(const CodePoint codePoint)
{
    static const std::unordered_map<CodePoint, CodePoint> SpecialCaseUpper{
        {CodePoint{0x00DF}, CodePoint{0x1E9E}}, // ß -> ẞ
        {CodePoint{0x0131}, CodePoint{0x0049}}, // ı -> I
        {CodePoint{0x0149}, CodePoint{0x02BC}}  // ŉ -> ’n
    };
    if (SpecialCaseUpper.find(codePoint) != SpecialCaseUpper.end())
    {
        return SpecialCaseUpper.at(codePoint);
    }
    // Latin
    if (codePoint >= 0x61 && codePoint <= 0x7A)
    {
        return codePoint - 0x20;
    }
    // Cirillic
    if (codePoint >= 0x430 && codePoint <= 0x44F)
    {
        return codePoint - 0x20;
    }
    // Greek
    if (codePoint >= 0x3B1 && codePoint <= 0x3C1)
    {
        return codePoint - 0x20;
    }
    if (codePoint >= 0x3C3 && codePoint <= 0x3C9)
    {
        return codePoint - 0x20;
    }
    // Additional
    if (codePoint >= 0x1F00 && codePoint <= 0x1F07)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F10 && codePoint <= 0x1F15)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F20 && codePoint <= 0x1F27)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F30 && codePoint <= 0x1F37)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F40 && codePoint <= 0x1F45)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F60 && codePoint <= 0x1F67)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F70 && codePoint <= 0x1F71)
    {
        return codePoint + 0x56;
    }
    if (codePoint >= 0x1F72 && codePoint <= 0x1F75)
    {
        return codePoint + 0x64;
    }
    if (codePoint >= 0x1F76 && codePoint <= 0x1F77)
    {
        return codePoint + 0x80;
    }
    if (codePoint >= 0x1F78 && codePoint <= 0x1F79)
    {
        return codePoint + 0x7E;
    }
    if (codePoint >= 0x1F7A && codePoint <= 0x1F7B)
    {
        return codePoint + 0x7C;
    }
    if (codePoint >= 0x1F7C && codePoint <= 0x1F7D)
    {
        return codePoint + 0x7A;
    }
    // Ranges for Latin characters with diacritics
    if (codePoint >= 0x0100 && codePoint <= 0x012F)
    {
        if (codePoint % 2 == 0)
        {
            return codePoint;
        }
        return codePoint - 1;
    }
    if (codePoint >= 0x0132 && codePoint <= 0x0137)
    {
        if (codePoint % 2 == 0)
        {
            return codePoint;
        }
        return codePoint - 1;
    }
    if (codePoint >= 0x0139 && codePoint <= 0x0148)
    {
        if (codePoint % 2 == 0)
        {
            return codePoint;
        }
        return codePoint - 1;
    }
    if (codePoint >= 0x014A && codePoint <= 0x0177)
    {
        if (codePoint % 2 == 0)
        {
            return codePoint;
        }
        return codePoint - 1;
    }
    return codePoint;
}

inline CodePoint ToLowercase(const CodePoint codePoint)
{
    static const std::unordered_map<CodePoint, CodePoint> SpecialCaseLower{
        {CodePoint{0x1E9E}, CodePoint{0x00DF}}, // ẞ -> ß
        {CodePoint{0x0130}, CodePoint{0x0069}}, // İ -> i
        {CodePoint{0x212A}, CodePoint{0x006B}}, // K -> k
        {CodePoint{0x212B}, CodePoint{0x00E5}}  // Å -> å
    };
    if (SpecialCaseLower.find(codePoint) != SpecialCaseLower.end())
    {
        return SpecialCaseLower.at(codePoint);
    }
    // Latin
    if (codePoint >= 0x41 && codePoint <= 0x5A)
    {
        return codePoint + 0x20;
    }
    // Cirillic
    if (codePoint >= 0x410 && codePoint <= 0x42F)
    {
        return codePoint + 0x20;
    }
    // Greek
    if (codePoint >= 0x391 && codePoint <= 0x3A1)
    {
        return codePoint + 0x20;
    }
    if (codePoint >= 0x3A3 && codePoint <= 0x3A9)
    {
        return codePoint + 0x20;
    }
    // Aditional
    if (codePoint >= 0x1F08 && codePoint <= 0x1F0F)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F18 && codePoint <= 0x1F1D)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F28 && codePoint <= 0x1F2F)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F38 && codePoint <= 0x1F3F)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F48 && codePoint <= 0x1F4D)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1F68 && codePoint <= 0x1F6F)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1FB8 && codePoint <= 0x1FB9)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1FBA && codePoint <= 0x1FBB)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1FC8 && codePoint <= 0x1FCB)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1FD8 && codePoint <= 0x1FD9)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1FE8 && codePoint <= 0x1FE9)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1FEA && codePoint <= 0x1FEB)
    {
        return codePoint - 0x08;
    }
    if (codePoint >= 0x1FEC)
    {
        return codePoint - 0x08;
    }
    // Ranges for Latin characters with diacritics
    if (codePoint >= 0x0100 && codePoint <= 0x012F)
    {
        if (codePoint % 2 != 0)
        {
            return codePoint;
        }
        return codePoint + 1;
    }
    if (codePoint >= 0x0132 && codePoint <= 0x0137)
    {
        if (codePoint % 2 != 0)
        {
            return codePoint;
        }
        return codePoint + 1;
    }
    if (codePoint >= 0x0139 && codePoint <= 0x0148)
    {
        if (codePoint % 2 != 0)
        {
            return codePoint;
        }
        return codePoint + 1;
    }
    if (codePoint >= 0x014A && codePoint <= 0x0177)
    {
        if (codePoint % 2 != 0)
        {
            return codePoint;
        }
        return codePoint + 1;
    }
    return codePoint;
}

inline Char ToUppercase(const Char& value)
{
    return ToUppercase(value.GetCodePoint());
}

inline Char ToLowercase(const Char& value)
{
    return ToLowercase(value.GetCodePoint());
}

inline bool IsUppercase(const CodePoint codePoint)
{
    static const std::unordered_set<CodePoint> SpecialUppercase{
        CodePoint{0x1E9E}, // ẞ
        CodePoint{0x0130}, // İ
        CodePoint{0x212A}, // K
        CodePoint{0x212B}  // Å
    };
    if (SpecialUppercase.find(codePoint) != SpecialUppercase.end())
    {
        return true;
    }
    // Latin
    if (codePoint >= 0x41 && codePoint <= 0x5A)
    {
        return true;
    }
    // Cirillic
    if (codePoint >= 0x410 && codePoint <= 0x42F)
    {
        return true;
    }
    // Greek
    if (codePoint >= 0x391 && codePoint <= 0x3A1)
    {
        return true;
    }
    if (codePoint >= 0x3A3 && codePoint <= 0x3A9)
    {
        return true;
    }
    // Other ranges
    if (codePoint >= 0x1F08 && codePoint <= 0x1F0F)
    {
        return true;
    }
    if (codePoint >= 0x1F18 && codePoint <= 0x1F1D)
    {
        return true;
    }
    if (codePoint >= 0x1F28 && codePoint <= 0x1F2F)
    {
        return true;
    }
    if (codePoint >= 0x1F38 && codePoint <= 0x1F3F)
    {
        return true;
    }
    if (codePoint >= 0x1F48 && codePoint <= 0x1F4D)
    {
        return true;
    }
    if (codePoint >= 0x1F68 && codePoint <= 0x1F6F)
    {
        return true;
    }
    if (codePoint >= 0x1FB8 && codePoint <= 0x1FBB)
    {
        return true;
    }
    if (codePoint >= 0x1FC8 && codePoint <= 0x1FCB)
    {
        return true;
    }
    if (codePoint >= 0x1FD8 && codePoint <= 0x1FDB)
    {
        return true;
    }
    if (codePoint >= 0x1FE8 && codePoint <= 0x1FEC)
    {
        return true;
    }
    return false;
}

inline bool IsLowercase(const CodePoint codePoint)
{
    static const std::unordered_set<CodePoint> SpecialLowercase{
        CodePoint{0x00DF}, // ß
        CodePoint{0x0131}, // ı
        CodePoint{0x0149}  // ŉ
    };
    if (SpecialLowercase.find(codePoint) != SpecialLowercase.end())
    {
        return true;
    }
    // Latin
    if (codePoint >= 0x61 && codePoint <= 0x7A)
    {
        return true;
    }
    // Cirillic
    if (codePoint >= 0x430 && codePoint <= 0x44F)
    {
        return true;
    }
    // Greek
    if (codePoint >= 0x3B1 && codePoint <= 0x3C1)
    {
        return true;
    }
    if (codePoint >= 0x3C3 && codePoint <= 0x3C9)
    {
        return true;
    }
    // Other
    if (codePoint >= 0x1F00 && codePoint <= 0x1F07)
    {
        return true;
    }
    if (codePoint >= 0x1F10 && codePoint <= 0x1F15)
    {
        return true;
    }
    if (codePoint >= 0x1F20 && codePoint <= 0x1F27)
    {
        return true;
    }
    if (codePoint >= 0x1F30 && codePoint <= 0x1F37)
    {
        return true;
    }
    if (codePoint >= 0x1F40 && codePoint <= 0x1F45)
    {
        return true;
    }
    if (codePoint >= 0x1F60 && codePoint <= 0x1F67)
    {
        return true;
    }
    if (codePoint >= 0x1F70 && codePoint <= 0x1F7D)
    {
        return true;
    }
    return false;
}

inline bool IsLetter(const CodePoint codepoint)
{
    return IsUppercase(codepoint) || IsLowercase(codepoint);
}

inline int ToDigit(const CodePoint codepoint)
{
    if (codepoint >= 0x30 && codepoint <= 0x39)
    {
        return static_cast<int>(codepoint) - 0x30;
    }
    return -1;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_CHAR_UTILITY_H_
