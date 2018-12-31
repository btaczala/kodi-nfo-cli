#include <cxxopts.hpp>
#include "queryoptions.h"
#include "scrapper.h"

#include <fmt/format.h>

namespace {
const std::uint16_t defaultPopularityFilter = 5;
}

void search(const cxxopts::ParseResult& options, kfl::Scrapper& s) {
    try {
        kfl::QueryOptions queryOpts;
        queryOpts.push_back(
            std::make_pair("query", options["title"].as<std::string>()));

        if (options.count("y") != 0) {
            queryOpts.push_back(
                std::make_pair("year", options["y"].as<std::string>()));
        }

        auto titles = s.findTitle(queryOpts);

        if (options["a"].count() != 0) {
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
                                     title.release_date, title.title,
                                     title.popularity);
        }
    } catch (const cxxopts::OptionParseException& ex) {
        throw;
    }
}

void get(const cxxopts::ParseResult& options, kfl::Scrapper& s) {
    const auto entry = s.get(options["i"].as<std::uint32_t>());
    std::cout << entry.overview << "\n";
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

    using CommandCallback =
        std::function<void(const cxxopts::ParseResult&, kfl::Scrapper&)>;

    const std::vector<std::pair<std::string, CommandCallback> >
        availableCommands = {{"get", get}, {"search", search}};

    const auto fn =
        std::find_if(availableCommands.begin(), availableCommands.end(),
                     [&command](const auto& c) { return c.first == command; });

    if (fn != std::end(availableCommands)) {
        try {
            fn->second(options, s);
        } catch (const std::exception& ex) {
            std::cerr << ex.what() << "\n";
            std::cerr << opts.help({fn->first}) << "\n";
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
