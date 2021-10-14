//
// Created by desrumaux on 14/10/2021.
//

#include "JqApplication.hpp"

#include <iostream>
#include <fstream>

#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/Util/HelpFormatter.h>

#include "PocoJsonPath/JsonPath.hpp"

/**
 * Constructor
 */
JqApplication::JqApplication()
    : pretty(false)
    , helpRequired(false)
{}

/**
 * Define options
 *
 * @param options
 */
void JqApplication::defineOptions(Poco::Util::OptionSet& options)
{
    Poco::Util::Application::defineOptions(options);
    options.addOption(Poco::Util::Option("help", "h", "display usage")
        .required(false)
        .repeatable(false)
        .callback(Poco::Util::OptionCallback<JqApplication>{this, &JqApplication::handleUsage}));
    options.addOption(Poco::Util::Option("file", "f", "load file")
          .required(false)
          .repeatable(false)
          .argument("path", true)
          .callback(Poco::Util::OptionCallback<JqApplication>{this, &JqApplication::handleFile}));
    options.addOption(Poco::Util::Option("pretty", "p", "prettify output")
          .required(false)
          .repeatable(false)
          .callback(Poco::Util::OptionCallback<JqApplication>{this, &JqApplication::handlePretty}));
}

/**
 * Print usage
 */
void JqApplication::usage()
{
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("-f <FILE> <QUERY>");
    helpFormatter.setHeader("JQ (c++ version) is a tool query information from file. LICENSE: MIT");
    helpFormatter.format(std::cout);
}

/**
 * Print usage
 *
 * @param name
 * @param value
 */
void JqApplication::handleUsage(const std::string& name, const std::string& value)
{
    helpRequired = true;
    stopOptionsProcessing();
}

/**
 * Load variables from files
 *
 * @param name
 * @param value
 */
void JqApplication::handleFile(const std::string& name, const std::string& value)
{
    std::ifstream ifstream{value, std::ios_base::in};
    if (ifstream.fail()) {
        std::cout << "fail to read: " << value;
        cancelStatus = ExitCode::EXIT_IOERR;
        return;
    }

    try {
        Poco::JSON::Parser parser;
        variables = parser.parse(ifstream);
    } catch (const std::exception& e) {
        std::cout << "fail to read: " << value << ". Error: " << e.what();
        cancelStatus = ExitCode::EXIT_IOERR;
    }
}

/**
 * Handle pretty option
 *
 * @param name
 * @param value
 */
void JqApplication::handlePretty(const std::string& name, const std::string& value)
{
    pretty = true;
}

/**
 * Execute a query
 *
 * @param args
 *
 * @return exit code
 */
int JqApplication::main(const std::vector<std::string>& args)
{
    if (helpRequired) {
        usage();
        return ExitCode::EXIT_USAGE;
    }

    if (cancelStatus.has_value()) {
        return cancelStatus.value();
    }

    if (args.size() > 0) {
        jsonPath = args.at(0);
    }

    if (!jsonPath.has_value()) {
        usage();
        return ExitCode::EXIT_NOINPUT;
    }

    if (!variables.has_value()) {
        Poco::JSON::Parser parser;
        try {
            variables = parser.parse(std::cin);
        } catch (const std::exception&) {}
    }

    if (!variables.has_value()) {
        usage();
        return ExitCode::EXIT_NOINPUT;
    }

    PocoJsonPath::JsonPath jp{jsonPath.value()};
    auto result = jp.query(variables.value());
    Poco::JSON::Stringifier::stringify(result, std::cout, pretty ? 4 : 0);
    return ExitCode::EXIT_OK;
}