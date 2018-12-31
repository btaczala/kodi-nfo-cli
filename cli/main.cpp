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
        ("h,help", "Print help message")
        ("c,command", "Print help message", cxxopts::value<std::string>())
        ;
    opts.add_options("search")
        ("t,title", "Title to find",cxxopts::value<std::string>())
        ("y,year", "When the title was released", cxxopts::value<std::string>())
        ("a,all", "Include all results, don't limit")
        ;
    opts.add_options("get")
        ("i,id", "Id of the movie", cxxopts::value<std::uint32_t>())
        ;
    // clang-format on

    const auto options = opts.parse(argc, argv);

    if (options.count("h") != 0) {
        std::cout << opts.help({"", "search", "get"}) << "\n";
        return EXIT_SUCCESS;
    }

    if (options.count("command") == 0) {
        std::cerr << "Command is missing\n";
        std::cerr << opts.help({""}) << "\n";
        return EXIT_FAILURE;
    }

    const std::string command = options["command"].as<std::string>();

    kfl::Scrapper s;
    kfl::QueryOptions queryOpts;

    if (command == "search") {
        if (options.count("t") == 0) {
            std::cerr << opts.help({"search"}) << "\n";
            return EXIT_FAILURE;
        }
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

        for (const auto& title : titles) {
            std::cout << fmt::format("{:10} - [{}] {} {:4}\n", title.id,
                                     title.releaseDate, title.title,
                                     title.popularity);
        }
    } else if (command == "get") {
        if (options.count("i") == 0) {
            std::cerr << opts.help({"get"}) << "\n";
            return EXIT_FAILURE;
        }
        const auto entry = s.get(options["i"].as<std::uint32_t>());
        std::cout << entry.overview << "\n";
    }

    return 0;
}
