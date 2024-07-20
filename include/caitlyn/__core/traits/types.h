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

#ifndef CAITLIN_CORE_TRAITS_TYPES_H_
#define CAITLIN_CORE_TRAITS_TYPES_H_

#include "caitlyn/__core/traits/types/base.h"
#include "caitlyn/__core/traits/types/composite.h"
#include "caitlyn/__core/traits/types/operations.h"
#include "caitlyn/__core/traits/types/pointers.h"
#include "caitlyn/__core/traits/types/primary.h"
#include "caitlyn/__core/traits/types/properties.h"
#include "caitlyn/__core/traits/types/property_queries.h"
#include "caitlyn/__core/traits/types/references.h"
#include "caitlyn/__core/traits/types/relationships.h"
#include "caitlyn/__core/traits/types/sign_modifiers.h"
#include "caitlyn/__core/traits/types/specifiers.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <bool Condition, typename Ret = void>
using required = required_t<Condition, Ret>;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLIN_CORE_TRAITS_TYPES_H_
