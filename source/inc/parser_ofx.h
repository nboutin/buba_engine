
#pragma once

#include <string>
#include <tuple>

#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

namespace buba
{
class Parser_OFX
{
public:
    Parser_OFX(const std::string& pathname);

    const pt::ptree& get_tree() const { return m_tree; }

private:
    pt::ptree m_tree;
};
}
