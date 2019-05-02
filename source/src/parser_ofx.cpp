
#include "parser_ofx.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;
using namespace buba;
using namespace std;

void print(const pt::ptree& tree);

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
                    if(!path_current.empty())
                        path_current += ".";

                    path_current += tag;
                }
                else
                {
                    auto leaf = path_current + "." + tag;
                    cout << "leaf:" << leaf << ":" << value << endl;
                    tree.add(leaf, value);
                }
            }
            else
            {
                // a.b.c
                auto tag     = line.substr(start2 + 1, end - 1);
                auto n       = path_current.find_last_of('.');
                path_current = path_current.substr(0, n);
                cout << "close:" << path_current << endl;
            }
        }
    }

    print(tree);
}

// struct ptree
//{
//   data_type data;                         // data associated with the node
//   list< pair<key_type, ptree> > children; // ordered list of named children
//};

void print(const pt::ptree& tree)
{
    if(tree.empty())
    {
        cout << "value:" << tree.data() << endl;
        return;
    }

    for(auto i : tree)
    {
        auto node = i.first;
        if(!node.empty())
        {
            cout << "node:" << i.first << endl;
        }
        print(i.second);
    }
}
