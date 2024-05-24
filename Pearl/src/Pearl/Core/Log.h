//
// Created by Andrew Graser on 5/23/2024.
//

#ifndef PEARL_LOG_H
#define PEARL_LOG_H

#include <cstdio>
#include <windows.h>


namespace Pearl {
    class Log {
    public:
        static int Print(const char* format, ...);

    private:
        static int VDebugPrint(const char* format, va_list args);
    };
}


#endif //PEARL_LOG_H
