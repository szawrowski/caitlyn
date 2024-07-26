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

#ifndef CAITLYN_CORE_ERROR_EXPECTED_H_
#define CAITLYN_CORE_ERROR_EXPECTED_H_

#include <stdexcept>
#include <type_traits>
#include <utility>

#include "Caitlyn/__Core/Error/Unexpected.h"
#include "Caitlyn/__Core/Traits.h"
#include "Caitlyn/__Core/Utility.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T, typename E>
class Expected
{
public:
    using ValueType = T;
    using ErrorType = E;

    Expected(const ValueType& value) : hasValue_{true}
    {
        new (&data_.value) ValueType{value};
    }

    Expected(ValueType&& value) : hasValue_{true}
    {
        new (&data_.value) ValueType{std::move(value)};
    }

    Expected(const Unexpected<ErrorType>& error) : hasValue_{false}
    {
        new (&data_.error) Unexpected<ErrorType>{error};
    }

    Expected(Unexpected<ErrorType>&& error) : hasValue_{false}
    {
        new (&data_.error) Unexpected<ErrorType>{std::move(error)};
    }

    Expected(const Expected& other) : hasValue_{other.hasValue_}
    {
        if (other.hasValue_)
        {
            new (&data_.value) ValueType{other.data_.value};
        }
        else
        {
            new (&data_.error) Unexpected<ErrorType>{other.data_.error};
        }
    }

    Expected& operator=(const Expected& other)
    {
        if (this != &other)
        {
            DestroyUnion();
            hasValue_ = other.hasValue_;
            if (hasValue_)
            {
                new (&data_.value) ValueType{other.data_.value};
            }
            else
            {
                new (&data_.error) Unexpected<ErrorType>{other.data_.error};
            }
        }
        return *this;
    }

    Expected(Expected&& other) noexcept(NothrowMoveConstructible<ValueType>() && NothrowMoveConstructible<ErrorType>())
        : hasValue_(other.hasValue_)
    {
        if (hasValue_)
        {
            new (&data_.value) ValueType{std::move(other.data_.value)};
        }
        else
        {
            new (&data_.error) Unexpected<ErrorType>{std::move(other.data_.error)};
        }
    }

    Expected& operator=(Expected&& other)
        noexcept(NothrowMoveAssignable<ValueType>() && NothrowMoveAssignable<ErrorType>())
    {
        if (this != &other)
        {
            DestroyUnion();
            hasValue_ = other.hasValue_;
            if (hasValue_)
            {
                new (&data_.value) ValueType{std::move(other.data_.value)};
            }
            else
            {
                new (&data_.error) Unexpected<ErrorType>{std::move(other.data_.error)};
            }
        }
        return *this;
    }

    ~Expected()
    {
        DestroyUnion();
    }

    explicit operator bool() const noexcept
    {
        return hasValue_;
    }

    bool HasValue() const noexcept
    {
        return hasValue_;
    }

    bool HasError() const noexcept
    {
        return !hasValue_;
    }

    const ValueType& Get() const
    {
        if (hasValue_)
        {
            return data_.value;
        }
        throw std::logic_error{"Called Get() on an error result"};
    }

    const ErrorType& GetError() const
    {
        if (!hasValue_)
        {
            return data_.error.Get();
        }
        throw std::logic_error{"Called Get_error() on a non-error result"};
    }

    template <typename Func>
    auto Map(Func func) const -> Expected<typename std::result_of<Func(const ValueType&)>::type, ErrorType>
    {
        using result_ValueType = typename std::result_of<Func(const ValueType&)>::type;
        if (hasValue_)
        {
            return Expected<result_ValueType, ErrorType>{func(data_.value)};
        }
        return Expected<result_ValueType, ErrorType>{data_.error};
    }

    template <typename Func>
    auto MapError(Func func) const -> Expected<ValueType, typename std::result_of<Func(const ErrorType&)>::type>
    {
        using result_error_type = typename std::result_of<Func(const ErrorType&)>::type;
        if (!hasValue_)
        {
            return Expected<ValueType, result_error_type>(Unexpected<result_error_type>(func(data_.error.Get())));
        }
        return *this;
    }

    template <typename Func>
    auto AndThen(Func func) const -> Expected
    {
        if (hasValue_)
        {
            return func(data_.value);
        }
        return *this;
    }

    template <typename Func>
    auto OrElse(Func func) const -> Expected
    {
        if (!hasValue_)
        {
            return func(data_.error.Get());
        }
        return *this;
    }

    template <typename U>
    ValueType UnwrapOr(const U& value) const
    {
        if (hasValue_)
        {
            return data_.value;
        }
        return value;
    }

    template <typename ErrFunc>
    auto UnwrapOrElse(ErrFunc func) const -> decltype(func(std::declval<Unexpected<ErrorType>>().Get()))
    {
        if (hasValue_)
        {
            return data_.value;
        }
        return func(data_.error.Get());
    }

    const ValueType& UnwrapOrDefault() const
    {
        static ValueType default_value{};
        return unwrap_or(default_value);
    }

    const ValueType& UnwrapOrDefault(const ValueType& default_value) const
    {
        return unwrap_or(default_value);
    }

    const ValueType& Expect(const String& message) const
    {
        if (hasValue_)
        {
            return data_.value;
        }
        throw std::runtime_error(message.str());
    }

    template <typename U>
    auto ExpectError(const U& message) const -> const ErrorType&
    {
        if (!hasValue_)
        {
            return data_.error.Get();
        }
        throw std::runtime_error(message);
    }

    template <typename Func>
    auto Filter(Func func) const -> Expected
    {
        if (hasValue_ && func(data_.value))
        {
            return *this;
        }
        return result_t(Unexpected<ErrorType>{});
    }

    template <typename U, typename Func>
    auto Fold(U&& init, Func&& f) const -> decltype(f(std::declval<U>(), std::declval<ValueType>()))
    {
        if (hasValue_)
        {
            return f(std::forward<U>(init), data_.value);
        }
        return std::forward<U>(init);
    }

    template <typename Func>
    auto Then(Func func) const -> Expected
    {
        if (hasValue_)
        {
            return func(data_.value);
        }
        return *this;
    }

    template <typename Func>
    auto CatchError(Func func) const -> Expected
    {
        if (!hasValue_)
        {
            return func(data_.error.Get());
        }
        return *this;
    }

    template <typename Func>
    auto OnError(Func func) const -> Expected
    {
        if (!hasValue_)
        {
            func(data_.error.Get());
        }
        return *this;
    }

    template <typename Func>
    auto Customize(Func&& func) const -> decltype(func(*this))
    {
        return func(*this);
    }

    template <typename TFunc, typename EFunc, typename... Args>
    auto Inspect(TFunc value_func, EFunc error_func, Args&&... args) const
        -> decltype(value_func(std::declval<ValueType>(), std::forward<Args>(args)...))
    {
        if (hasValue_)
        {
            return value_func(data_.value, std::forward<Args>(args)...);
        }
        return error_func(data_.error.Get(), std::forward<Args>(args)...);
    }

private:
    template <typename Result = T, typename Error = E>
    Required<Destructible<Result>() && !Destructible<Error>()> DestroyUnion()
    {
        if (hasValue_)
        {
            data_.value.~ValueType();
        }
    }

    template <typename Result = T, typename Error = E>
    Required<!Destructible<Result>() && Destructible<Error>()> DestroyUnion()
    {
        if (!hasValue_)
        {
            data_.error.~Unexpected<ErrorType>();
        }
    }

    template <typename Result = T, typename Error = E>
    Required<Destructible<Result>() && Destructible<Error>()> DestroyUnion()
    {
        if (hasValue_)
        {
            data_.value.~ValueType();
        }
        else
        {
            data_.error.~Unexpected<ErrorType>();
        }
    }

    template <typename Result = T, typename Error = E>
    Required<!Destructible<Result>() && !Destructible<Error>()> DestroyUnion()
    {
    }

private:
    union DataUnion
    {
        ValueType value;
        Unexpected<ErrorType> error;

        DataUnion()
        {
        }

        ~DataUnion()
        {
        }
    } data_;

    bool hasValue_;
};

template <typename T, typename E>
Expected<T, E> MakeCorrect(T value)
{
    return Expected<T, E>{std::move(value)};
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_ERROR_EXPECTED_H_
