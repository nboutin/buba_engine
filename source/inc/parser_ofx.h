
#pragma once

#include <string>
#include <tuple>

namespace buba
{
class Parser_OFX
{
public:
    Parser_OFX(const std::string& pathname);

private:
    std::tuple<std::string, std::string> parse_line(const std::string& line);
};
}
