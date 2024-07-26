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

#ifndef CAITLYN_CORE_CHAR_DEFS_H_
#define CAITLYN_CORE_CHAR_DEFS_H_

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_DEF_NAMESPACE_BEGIN

constexpr auto Null = "\x00";                        // NULL
constexpr auto StartOfHeading = "\x01";              // START OF HEADING
constexpr auto StartOfText = "\x02";                 // START OF TEXT
constexpr auto EndOfText = "\x03";                   // END OF TEXT
constexpr auto EndOfTransmission = "\x04";           // END OF TRANSMISSION
constexpr auto Enquiry = "\x05";                     // ENQUIRY
constexpr auto Acknowledge = "\x06";                 // ACKNOWLEDGE
constexpr auto Bell = "\x07";                        // BELL
constexpr auto Backspace = "\x08";                   // BACKSPACE
constexpr auto CharacterTabulation = "\x09";         // CHARACTER TABULATION
constexpr auto LineFeed = "\x0A";                    // LINE FEED (LF)
constexpr auto LineTabulation = "\x0B";              // LINE TABULATION
constexpr auto FormFeed = "\x0C";                    // FORM FEED (FF)
constexpr auto CarriageReturn = "\x0D";              // CARRIAGE RETURN (CR)
constexpr auto ShiftOut = "\x0E";                    // SHIFT OUT
constexpr auto ShiftIn = "\x0F";                     // SHIFT IN
constexpr auto DataLinkEscape = "\x10";              // DATA LINK ESCAPE
constexpr auto DeviceControlOne = "\x11";            // DEVICE CONTROL ONE
constexpr auto DeviceControlTwo = "\x12";            // DEVICE CONTROL TWO
constexpr auto DeviceControlThree = "\x13";          // DEVICE CONTROL THREE
constexpr auto DeviceControlFour = "\x14";           // DEVICE CONTROL FOUR
constexpr auto NegativeAcknowledge = "\x15";         // NEGATIVE ACKNOWLEDGE
constexpr auto SynchronousIdle = "\x16";             // SYNCHRONOUS IDLE
constexpr auto EndOfTransmissionBlock = "\x17";      // END OF TRANSMISSION BLOCK
constexpr auto Cancel = "\x18";                      // CANCEL
constexpr auto EndOfMedium = "\x19";                 // END OF MEDIUM
constexpr auto Substitute = "\x1A";                  // SUBSTITUTE
constexpr auto Escape = "\x1B";                      // ESCAPE
constexpr auto InformationSeparatorFour = "\x1C";    // INFORMATION SEPARATOR FOUR
constexpr auto InformationSeparatorThree = "\x1D";   // INFORMATION SEPARATOR THREE
constexpr auto InformationSeparatorTwo = "\x1E";     // INFORMATION SEPARATOR TWO
constexpr auto InformationSeparatorOne = "\x1F";     // INFORMATION SEPARATOR ONE
constexpr auto Space = "\x20";                       // SPACE
constexpr auto ExclamationMark = "\x21";             // EXCLAMATION MARK
constexpr auto QuotationMark = "\x22";               // QUOTATION MARK
constexpr auto NumberSign = "\x23";                  // NUMBER SIGN
constexpr auto DollarSign = "\x24";                  // DOLLAR SIGN
constexpr auto PercentSign = "\x25";                 // PERCENT SIGN
constexpr auto Ampersand = "\x26";                   // AMPERSAND
constexpr auto Apostrophe = "\x27";                  // APOSTROPHE
constexpr auto LeftParenthesis = "\x28";             // LEFT PARENTHESIS
constexpr auto RightParenthesis = "\x29";            // RIGHT PARENTHESIS
constexpr auto Asterisk = "\x2A";                    // ASTERISK
constexpr auto PlusSign = "\x2B";                    // PLUS SIGN
constexpr auto Comma = "\x2C";                       // COMMA
constexpr auto HyphenMinus = "\x2D";                 // HYPHEN-MINUS
constexpr auto FullStop = "\x2E";                    // FULL STOP
constexpr auto Solidus = "\x2F";                     // SOLIDUS
constexpr auto DigitZero = "\x30";                   // DIGIT ZERO
constexpr auto DigitOne = "\x31";                    // DIGIT ONE
constexpr auto DigitTwo = "\x32";                    // DIGIT TWO
constexpr auto DigitThree = "\x33";                  // DIGIT THREE
constexpr auto DigitFour = "\x34";                   // DIGIT FOUR
constexpr auto DigitFive = "\x35";                   // DIGIT FIVE
constexpr auto DigitSix = "\x36";                    // DIGIT SIX
constexpr auto DigitSeven = "\x37";                  // DIGIT SEVEN
constexpr auto DigitEight = "\x38";                  // DIGIT EIGHT
constexpr auto DigitNine = "\x39";                   // DIGIT NINE
constexpr auto Colon = "\x3A";                       // COLON
constexpr auto Semicolon = "\x3B";                   // SEMICOLON
constexpr auto LessThanSign = "\x3C";                // LESS-THAN SIGN
constexpr auto EqualsSign = "\x3D";                  // EQUALS SIGN
constexpr auto GreaterThanSign = "\x3E";             // GREATER-THAN SIGN
constexpr auto QuestionMark = "\x3F";                // QUESTION MARK
constexpr auto CommercialAt = "\x40";                // COMMERCIAL AT
constexpr auto LatinCapitalLetterA = "\x41";         // LATIN CAPITAL LETTER A
constexpr auto LatinCapitalLetterB = "\x42";         // LATIN CAPITAL LETTER B
constexpr auto LatinCapitalLetterC = "\x43";         // LATIN CAPITAL LETTER C
constexpr auto LatinCapitalLetterD = "\x44";         // LATIN CAPITAL LETTER D
constexpr auto LatinCapitalLetterE = "\x45";         // LATIN CAPITAL LETTER E
constexpr auto LatinCapitalLetterF = "\x46";         // LATIN CAPITAL LETTER F
constexpr auto LatinCapitalLetterG = "\x47";         // LATIN CAPITAL LETTER G
constexpr auto LatinCapitalLetterH = "\x48";         // LATIN CAPITAL LETTER H
constexpr auto LatinCapitalLetterI = "\x49";         // LATIN CAPITAL LETTER I
constexpr auto LatinCapitalLetterJ = "\x4A";         // LATIN CAPITAL LETTER J
constexpr auto LatinCapitalLetterK = "\x4B";         // LATIN CAPITAL LETTER K
constexpr auto LatinCapitalLetterL = "\x4C";         // LATIN CAPITAL LETTER L
constexpr auto LatinCapitalLetterM = "\x4D";         // LATIN CAPITAL LETTER M
constexpr auto LatinCapitalLetterN = "\x4E";         // LATIN CAPITAL LETTER N
constexpr auto LatinCapitalLetterO = "\x4F";         // LATIN CAPITAL LETTER O
constexpr auto LatinCapitalLetterP = "\x50";         // LATIN CAPITAL LETTER P
constexpr auto LatinCapitalLetterQ = "\x51";         // LATIN CAPITAL LETTER Q
constexpr auto LatinCapitalLetterR = "\x52";         // LATIN CAPITAL LETTER R
constexpr auto LatinCapitalLetterS = "\x53";         // LATIN CAPITAL LETTER S
constexpr auto LatinCapitalLetterT = "\x54";         // LATIN CAPITAL LETTER T
constexpr auto LatinCapitalLetterU = "\x55";         // LATIN CAPITAL LETTER U
constexpr auto LatinCapitalLetterV = "\x56";         // LATIN CAPITAL LETTER V
constexpr auto LatinCapitalLetterW = "\x57";         // LATIN CAPITAL LETTER W
constexpr auto LatinCapitalLetterX = "\x58";         // LATIN CAPITAL LETTER X
constexpr auto LatinCapitalLetterY = "\x59";         // LATIN CAPITAL LETTER Y
constexpr auto LatinCapitalLetterZ = "\x5A";         // LATIN CAPITAL LETTER Z
constexpr auto LeftSquareBracket = "\x5B";           // LEFT SQUARE BRACKET
constexpr auto ReverseSolidus = "\x5C";              // REVERSE SOLIDUS
constexpr auto RightSquareBracket = "\x5D";          // RIGHT SQUARE BRACKET
constexpr auto CircumflexAccent = "\x5E";            // CIRCUMFLEX ACCENT
constexpr auto LowLine = "\x5F";                     // LOW LINE
constexpr auto GraveAccent = "\x60";                 // GRAVE ACCENT
constexpr auto LatinSmallLetterA = "\x61";           // LATIN SMALL LETTER A
constexpr auto LatinSmallLetterB = "\x62";           // LATIN SMALL LETTER B
constexpr auto LatinSmallLetterC = "\x63";           // LATIN SMALL LETTER C
constexpr auto LatinSmallLetterD = "\x64";           // LATIN SMALL LETTER D
constexpr auto LatinSmallLetterE = "\x65";           // LATIN SMALL LETTER E
constexpr auto LatinSmallLetterF = "\x66";           // LATIN SMALL LETTER F
constexpr auto LatinSmallLetterG = "\x67";           // LATIN SMALL LETTER G
constexpr auto LatinSmallLetterH = "\x68";           // LATIN SMALL LETTER H
constexpr auto LatinSmallLetterI = "\x69";           // LATIN SMALL LETTER I
constexpr auto LatinSmallLetterJ = "\x6A";           // LATIN SMALL LETTER J
constexpr auto LatinSmallLetterK = "\x6B";           // LATIN SMALL LETTER K
constexpr auto LatinSmallLetterL = "\x6C";           // LATIN SMALL LETTER L
constexpr auto LatinSmallLetterM = "\x6D";           // LATIN SMALL LETTER M
constexpr auto LatinSmallLetterN = "\x6E";           // LATIN SMALL LETTER N
constexpr auto LatinSmallLetterO = "\x6F";           // LATIN SMALL LETTER O
constexpr auto LatinSmallLetterP = "\x70";           // LATIN SMALL LETTER P
constexpr auto LatinSmallLetterQ = "\x71";           // LATIN SMALL LETTER Q
constexpr auto LatinSmallLetterR = "\x72";           // LATIN SMALL LETTER R
constexpr auto LatinSmallLetterS = "\x73";           // LATIN SMALL LETTER S
constexpr auto LatinSmallLetterT = "\x74";           // LATIN SMALL LETTER T
constexpr auto LatinSmallLetterU = "\x75";           // LATIN SMALL LETTER U
constexpr auto LatinSmallLetterV = "\x76";           // LATIN SMALL LETTER V
constexpr auto LatinSmallLetterW = "\x77";           // LATIN SMALL LETTER W
constexpr auto LatinSmallLetterX = "\x78";           // LATIN SMALL LETTER X
constexpr auto LatinSmallLetterY = "\x79";           // LATIN SMALL LETTER Y
constexpr auto LatinSmallLetterZ = "\x7A";           // LATIN SMALL LETTER Z
constexpr auto LeftCurlyBracket = "\x7B";            // LEFT CURLY BRACKET
constexpr auto VerticalLine = "\x7C";                // VERTICAL LINE
constexpr auto RightCurlyBracket = "\x7D";           // RIGHT CURLY BRACKET
constexpr auto Tilde = "\x7E";                       // TILDE
constexpr auto Delete = "\x7F";                      // DELETE

__CAITLYN_DEF_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_CHAR_DEFS_H_
