//
// Created by desrumaux on 14/10/2021.
//

#ifndef POCOJSONPATH_JQAPPLICATION_HPP
#define POCOJSONPATH_JQAPPLICATION_HPP

#include <optional>

#include <Poco/Util/Application.h>
#include <Poco/Dynamic/Var.h>

class JqApplication : public Poco::Util::Application {
    bool helpRequired;
    bool pretty;
    std::optional<std::string> jsonPath;
    std::optional<Poco::Dynamic::Var> variables;
    std::optional<Poco::Util::Application::ExitCode> cancelStatus;
public:

    /**
     * Constructor
     */
    JqApplication();

    /**
     * Define options
     *
     * @param options
     */
    void defineOptions(Poco::Util::OptionSet& options);

    /**
     * Print usage
     */
    void usage();

    /**
     * Print usage
     *
     * @param name
     * @param value
     */
    void handleUsage(const std::string& name, const std::string& value);

    /**
     * Load variables from files
     *
     * @param name
     * @param value
     */
    void handleFile(const std::string& name, const std::string& value);

    /**
     * Handle pretty option
     *
     * @param name
     * @param value
     */
    void handlePretty(const std::string& name, const std::string& value);

    /**
     * Execute a query
     *
     * @param args
     *
     * @return exit code
     */
    int main(const std::vector<std::string>& args);

};


#endif //POCOJSONPATH_JQAPPLICATION_HPP
