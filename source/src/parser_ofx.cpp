
#include "parser_ofx.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace buba;
using namespace std;

Parser_OFX::Parser_OFX(const std::string& pathname)
{
    ifstream ifs(pathname);

    string line;

    while(ifs >> line)
    {
        string tag, value;
        tie(tag, value) = parse_line(line);

        cout << tag << endl;
    }
}

tuple<string, string> Parser_OFX::parse_line(const std::string& line)
{
    auto tag_start = line.find('<');
    //    auto end_tag_start = line.find("</");
    auto tag_end = line.find('>');

    if(tag_start != string::npos && tag_end != string::npos)
    {
        auto tag = line.substr(tag_start + 1, tag_end - 1);
        return make_tuple(tag, "");
    }

    return {"", ""};
}
