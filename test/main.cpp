#include "PocoJsonPath/JsonPath.hpp"

#include <iostream>
#include <fstream>
#include <Poco/JSON/Parser.h>

int main(int argc, char** argv)
{
    if (argc != 3) {
        return 1;
    }

    std::string jsonPath{argv[1]};
    std::string filePath{argv[2]};

    std::ifstream ifstream{filePath, std::ios_base::in};
    if (ifstream.fail()) {
        return 0;
    }

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var var = parser.parse(ifstream);

    PocoJsonPath::JsonPath jpath{jsonPath};
    auto r = jpath.query(var);
    Poco::JSON::Stringifier::stringify(r, std::cout, 4);
    return 0;
}