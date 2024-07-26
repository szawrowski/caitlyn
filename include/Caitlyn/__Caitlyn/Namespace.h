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

#ifndef CAITLYN_NAMESPACE_H_
#define CAITLYN_NAMESPACE_H_

#define __CAITLYN_GLOBAL_NAMESPACE_BEGIN namespace Caitlyn {
#define __CAITLYN_GLOBAL_NAMESPACE_END }

#define __CAITLYN_DETAIL_NAMESPACE_BEGIN namespace __Detail {
#define __CAITLYN_DETAIL_NAMESPACE_END }

#define __CAITLYN_DEF_NAMESPACE_BEGIN namespace Def {
#define __CAITLYN_DEF_NAMESPACE_END }

#define __CAITLYN_TRAITS_NAMESPACE_BEGIN namespace Traits {
#define __CAITLYN_TRAITS_NAMESPACE_END }

#define __CAITLYN_NUMERIC_NAMESPACE_BEGIN namespace Numeric {
#define __CAITLYN_NUMERIC_NAMESPACE_END }

#define __CAITLYN_JSON_NAMESPACE_BEGIN namespace Json {
#define __CAITLYN_JSON_NAMESPACE_END }

#define __CAITLYN_TESTING_NAMESPACE_BEGIN namespace Test {
#define __CAITLYN_TESTING_NAMESPACE_END }

#endif // CAITLYN_NAMESPACE_H_
