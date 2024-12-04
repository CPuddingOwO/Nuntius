#pragma once

#ifdef _WIN32
    #ifdef NUNTIUS_EXPORTS
        #define NT_API __declspec(dllexport)
    #else
        #define NT_API __declspec(dllimport)
    #endif
#else
    #define NT_API __attribute__((visibility("default")))
#endif