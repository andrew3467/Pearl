//
// Created by Andrew Graser on 5/23/2024.
//

#include <cstdint>
#include "Log.h"


namespace Pearl {

    int Log::Print(const char *format, ...) {
        va_list argList;
        va_start(argList, format);

        int charsWritten = VDebugPrint(format, argList);

        va_end(argList);
        return charsWritten;
    }

    int Log::VDebugPrint(const char *format, va_list args) {
        const uint32_t MAX_CHARS = 1024;
        static char buffer[MAX_CHARS];

        int charsWritten =
                vsnprintf(buffer, MAX_CHARS, format, args);

        OutputDebugString(buffer);

        return charsWritten;
    }
}