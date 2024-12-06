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

//#ifndef nuntius_STATIC
//    #if NUNTIUS_EXPORTS && (defined(_MSC_VER) || defined(__MINGW32__))
//        #define NT_API __declspec(dllexport)
//    #elif NUNTIUS_EXPORTS
//        #define NT_API __attribute__((__visibility__("default")))
//    #elif defined _MSC_VER
//        #define NT_API __declspec(dllimport)
//    #else
//        #define NT_API
//    #endif
//#else
//    #define NT_API
//#endif