#include <Nuntius/StringEx.hpp>

namespace nt {

    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> result;
        std::istringstream iss(str);
        std::string token;
        while (std::getline(iss, token, delimiter)) {
            result.push_back(token);
        }
        return result;
    }
}