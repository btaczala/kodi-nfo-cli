#include "tmdscrapper.h"
#include "config.h"

#include <fmt/format.h>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <json.hpp>

namespace {
const std::string kApiUrl = "https://api.themoviedb.org";
const std::string kApiVersion = "3";
}  // namespace

namespace kfl {
namespace themoviedb {
Scrapper::Scrapper() { curlpp::initialize(); }
Scrapper::~Scrapper() { curlpp::terminate(); }
std::vector<Info> Scrapper::findTitle(const QueryOptions& options) {
    std::vector<Info> searchResults;
    try {
        curlpp::Easy request;

        std::string url = fmt::format(
            "{url}/{apiVersion}/{command}/"
            "movie?api_key={apiKey}&language={language}",
            fmt::arg("url", kApiUrl), fmt::arg("apiVersion", kApiVersion),
            fmt::arg("apiKey", kfl::themoviedb::getApiKey()),
            fmt::arg("language", "en-US"), fmt::arg("command", "search"));
        for (const auto& option : options) {
            url.append(fmt::format("&{}={}", option.first, option.second));
        }

        std::string response;
        curlpp::Types::WriteFunctionFunctor fn =
            [&response](char* bytes, size_t size, size_t nbytes) -> size_t {
            response.append(const_cast<const char*>(bytes), nbytes);
            return nbytes * size;
        };
        request.setOpt(new curlpp::Options::WriteFunction(fn));

        std::cout << url << "\n";
        request.setOpt(curlpp::Options::Url(url));
        request.perform();

        const auto json = nlohmann::json::parse(response);

        // searchResults.resize(json["total_results"].get<std::uint32_t>());

        const auto resultList = json["results"];
        // for (const auto& v : resultList) {
        //}
        std::transform(resultList.begin(), resultList.end(),
                       std::back_inserter(searchResults),
                       [](const nlohmann::json& entry) {
                           return Info{
                               entry["id"].get<std::uint32_t>(),
                               entry["title"].get<std::string>(),
                               entry["release_date"].get<std::string>(),
                               entry["popularity"].get<double>(),
                           };
                       });
    } catch (const std::exception& ex) {
    }
    return searchResults;
}

}  // namespace themoviedb
}  // namespace kfl
