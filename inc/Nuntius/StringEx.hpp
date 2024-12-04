#pragma once

#include <Nuntius/API.hpp>

#include <string>
#include <sstream>
#include <vector>

namespace nt {
    std::vector<std::string> NT_API split(const std::string& str, char delimiter);
}