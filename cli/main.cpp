#include <cxxopts.hpp>
#include "queryoptions.h"
#include "scrapper.h"

#include <fmt/format.h>

int main(int argc, char *argv[]) {
    using namespace cxxopts;
    Options opts{"kodi-nfo-cli", ""};

    opts.add_options()("t,title", "Title to find",
                       cxxopts::value<std::string>())(
        "y,year", "When the title was released", cxxopts::value<std::string>());
    const auto options = opts.parse(argc, argv);

    if (options.count("t") == 0) {
        std::cerr << opts.help() << "\n";
        return EXIT_FAILURE;
    }

    kfl::Scrapper s;
    kfl::QueryOptions queryOpts;
    queryOpts.push_back(
        std::make_pair("query", options["t"].as<std::string>()));
    if (options.count("y") != 0) {
        queryOpts.push_back(
            std::make_pair("year", options["y"].as<std::string>()));
    }

    auto titles = s.findTitle(queryOpts);
    std::sort(titles.begin(), titles.end(), [](auto lhs, auto rhs) {
        return lhs.popularity > rhs.popularity;
    });

    for (auto title : titles) {
        std::cout << fmt::format("{:10} - [{}] {} {:4}\n", title.id,
                                 title.releaseDate, title.title,
                                 title.popularity);
    }
    return 0;
}
