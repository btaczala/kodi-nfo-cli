#include <cxxopts.hpp>
#include "scrapper.h"

int main(int argc, char *argv[]) {
    using namespace cxxopts;
    Options opts{"kodi-nfo-cli", ""};

    opts.add_options()("t,title", "Title to find",
                       cxxopts::value<std::string>());
    const auto options = opts.parse(argc, argv);

    if (options.count("t") == 0) {
        std::cerr << opts.help() << "\n";
        return EXIT_FAILURE;
    }

    kfl::Scrapper s;
    s.findTitle(options["t"].as<std::string>());
    return 0;
}
