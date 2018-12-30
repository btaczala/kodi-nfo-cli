#include "tmdscrapper.h"
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <fmt/format.h>

#include "config.h"

namespace {
const std::string kApiUrl = "https://api.themoviedb.org";
const std::string kApiVersion = "3";
}  // namespace

namespace kfl {
namespace themoviedb {
Scrapper::Scrapper() { curlpp::initialize(); }
Scrapper::~Scrapper() { curlpp::terminate(); }
void Scrapper::findTitle(const std::string& title) {
    curlpp::Easy request;
    const std::string url = fmt::format(
        "{url}/{apiVersion}/{command}/"
        "movie?api_key={apiKey}&language={language}&query={query}&page=1&"
        "include_adult=false",
        fmt::arg("url", kApiUrl), fmt::arg("apiVersion", kApiVersion),
        fmt::arg("apiKey", kfl::themoviedb::getApiKey()),
        fmt::arg("query", title), fmt::arg("language", "en-US"),
        fmt::arg("command", "search"));

    std::cout << url << "\n";
    request.setOpt(curlpp::Options::Url(url));

    request.perform();
    std::cout << request << "\n";
}

}  // namespace themoviedb
}  // namespace kfl
