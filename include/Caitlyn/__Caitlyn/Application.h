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

#ifndef CAITLYN_APPLICATION_H_
#define CAITLYN_APPLICATION_H_

#include <cstring>
#include <ios>
#include <stdexcept>
#include <vector>

#include "Caitlyn/__Caitlyn/Config.h"
#include "Caitlyn/__Caitlyn/Types.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

class Application
{
public:
    static const Application* Initialize()
    {
        if (initialized_)
        {
            throw std::runtime_error("Caitlyn::Initialize can only be called once.");
        }
        initialized_ = true;
        return new Application{};
    }

    static const Application* Initialize(const int& argc, const char** argv)
    {
        if (initialized_)
        {
            throw std::runtime_error("caitlyn::init can only be called once.");
        }
        initialized_ = true;
        return new Application{argc, argv};
    }

    const std::vector<const char*>& GetArgs() const
    {
        return args_;
    }

    const char* GetSystemName() const
    {
        return systemName_;
    }

    const char* GetCompilerInfo() const
    {
        return compiler_;
    }

    const char* GetCaitlynInfo() const
    {
        return libVersion_;
    }

private:
    Application()
        : libVersion_{__CAITLYN_VERSION},
          systemName_{__CAITLYN_OS_NAME},
          compiler_{__CAITLYN_COMPILER_VERSION}
    {
        configure();
    }

    Application(const int argc, const char** argv)
        : libVersion_{__CAITLYN_VERSION},
          systemName_{__CAITLYN_OS_NAME},
          compiler_{__CAITLYN_COMPILER_VERSION}
    {
        if (argc > 0)
        {
            args_.reserve(argc);
            for (int i = 0; i < argc; ++i)
            {
                auto arg_copy = new char[std::strlen(argv[i]) + 1];
                std::strcpy(arg_copy, argv[i]);
                args_.emplace_back(arg_copy);
            }
        }
        configure();
    }

    ~Application()
    {
        for (const char* arg : args_)
        {
            delete[] arg;
        }
    }

private:
    static void configure()
    {
#ifdef __CAITLYN_OS_WINDOWS
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif
        std::ios::sync_with_stdio(false);
    }

private:
    std::vector<const char*> args_{};
    const char* libVersion_;
    const char* systemName_;
    const char* compiler_;
    static bool initialized_;
};

bool Application::initialized_ = false;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_APPLICATION_H_
