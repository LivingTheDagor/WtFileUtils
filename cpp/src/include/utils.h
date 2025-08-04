//
// Created by sword on 8/3/2025.
//

#ifndef MYEXTENSION_UTILS_H
#define MYEXTENSION_UTILS_H
#include <format>
#include <iostream>
#include <cstdlib>
#include <cstdarg>  // for va_list, va_start, va_end

[[noreturn]] inline void fatal(const char* file, int line, const char* format, ...)
{
    std::fprintf(stderr, "Fatal error at %s:%d - ", file, line);

    va_list args;
    va_start(args, format);
    std::vfprintf(stderr, format, args);
    va_end(args);

    std::fprintf(stderr, "\n");
    std::exit(EXIT_FAILURE);
}

#define EXCEPTION(...) fatal(__FILE__, __LINE__, __VA_ARGS__)

#endif //MYEXTENSION_UTILS_H
