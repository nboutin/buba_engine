
#include "parser_ofx.h"

#include <fstream>
#include <iostream>
#include <string>

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <exception>
#include <iostream>
#include <set>
#include <string>
namespace pt = boost::property_tree;

using namespace buba;
using namespace std;

Parser_OFX::Parser_OFX(const std::string& pathname)
{
    // Create empty property tree object
    pt::ptree tree;
    string path_current;

    ifstream ifs(pathname);
    string line;

    while(ifs >> line)
    {
        auto start  = line.find('<');
        auto start2 = line.find("</");
        auto end    = line.find('>');

        if(start != string::npos && end != string::npos)
        {
            if(start2 == string::npos)
            {
                auto tag   = line.substr(start + 1, end - 1);
                auto value = line.substr(end + 1);

                if(value.empty())
                {
                    path_current += tag;
                    path_current += ".";
                }
                else
                {
                    cout << tag << ":" << value << endl;
                }
            }
            else
            {
                auto tag     = line.substr(start2 + 1, end - 1);
                auto n       = path_current.find_last_of('.');
                path_current = path_current.substr(0, n);
            }
        }

        cout << path_current << endl;
    }
}
