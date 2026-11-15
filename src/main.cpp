#include "depsort/package.hpp"

#include <CLI/CLI.hpp>

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    CLI::App app{"depsort - sort packages so dependencies come first"};
    app.set_version_flag("--version", std::string{depsort::version()});

    std::string input_file;
    app.add_option("file", input_file, "JSON file with package definitions")
        ->required()
        ->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    // TODO: read the file, call load_packages(), sort, print the result.
    std::cout << "Reading " << input_file << " (sorting not implemented yet)\n";
    return 0;
}
