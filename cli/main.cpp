#include <cxxopts.hpp>
#include "queryoptions.h"
#include "scrapper.h"

#include <fmt/format.h>

namespace {
const std::uint16_t defaultPopularityFilter = 5;
}

int main(int argc, char* argv[]) {
    using namespace cxxopts;
    Options opts{"kodi-nfo-cli", ""};

    // clang-format off
    opts.add_options()
        ("t,title", "Title to find",cxxopts::value<std::string>())
        ("y,year", "When the title was released", cxxopts::value<std::string>())
        ("a,all", "Include all results, don't limit")
        ;
    // clang-format on
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

    if (options.count("a") == 0) {
        titles.erase(std::remove_if(titles.begin(), titles.end(),
                                    [](const auto& title) {
                                        return title.popularity <
                                               defaultPopularityFilter;
                                    }),
                     titles.end());
    }

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
