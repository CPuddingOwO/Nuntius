#pragma once
#include <Nuntius/API.hpp>

namespace nt::fileserver {
    template <typename T>
    class NT_API IFileServer {
    public:
        virtual ~IFileServer() = default;
        virtual const IFileServer& read(const char* path, T& data) = 0;
        virtual const IFileServer& write(const char* path, const T& data) = 0;
    };
}