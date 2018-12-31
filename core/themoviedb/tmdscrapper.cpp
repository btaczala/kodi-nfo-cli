#include "tmdscrapper.h"
#include "config.h"

#include <fmt/format.h>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <json.hpp>

#include <iomanip>
#include <sstream>

namespace {
const std::string kApiUrl = "https://api.themoviedb.org";
const std::string kApiVersion = "3";

std::string encode_as_uri(const std::string& str) {
    std::vector<std::string> ret;

    std::transform(str.begin(), str.end(), std::back_inserter(ret),
                   [](char c) -> std::string {
                       if (std::isalnum(c) || c == '-' || c == '_' ||
                           c == '.' || c == '~') {
                           return std::string{c};
                       }
                       std::ostringstream escaped;
                       escaped.fill('0');
                       escaped << std::hex;
                       escaped << std::uppercase;
                       escaped << '%' << std::setw(2) << int((unsigned char)c);
                       escaped << std::nouppercase;

                       return escaped.str();
                   });

    using namespace std::literals;
    return std::accumulate(ret.begin(), ret.end(), ""s);
}

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
            url.append(fmt::format("&{}={}", option.first,
                                   encode_as_uri(option.second)));
        }

        std::string response;
        curlpp::Types::WriteFunctionFunctor fn =
            [&response](char* bytes, size_t size, size_t nbytes) -> size_t {
            response.append(const_cast<const char*>(bytes), nbytes);
            return nbytes * size;
        };
        request.setOpt(new curlpp::Options::WriteFunction(fn));

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

FullMovieEntry Scrapper::get(std::uint32_t id) {
    try {
        curlpp::Easy request;

        std::string url = fmt::format(
            "{url}/{apiVersion}/"
            "movie/{movie_id}?api_key={apiKey}&language={language}",
            fmt::arg("url", kApiUrl), fmt::arg("apiVersion", kApiVersion),
            fmt::arg("apiKey", kfl::themoviedb::getApiKey()),
            fmt::arg("movie_id", id), fmt::arg("language", "en-US"));

        std::string response;
        curlpp::Types::WriteFunctionFunctor fn =
            [&response](char* bytes, size_t size, size_t nbytes) -> size_t {
            response.append(const_cast<const char*>(bytes), nbytes);
            return nbytes * size;
        };
        request.setOpt(new curlpp::Options::WriteFunction(fn));

        request.setOpt(curlpp::Options::Url(url));
        request.perform();

        const auto json = nlohmann::json::parse(response);
        return FullMovieEntry{json["id"], json["title"], json["tagline"],
                              json["overview"], json["release_date"]};

    } catch (const std::exception& ex) {
    }
    return FullMovieEntry{};
}

}  // namespace themoviedb
}  // namespace kfl
