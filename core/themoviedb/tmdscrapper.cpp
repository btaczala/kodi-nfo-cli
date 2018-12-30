#include "tmdscrapper.h"
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

namespace kfl {
namespace themoviedb {
Scrapper::Scrapper() { curlpp::initialize(); }
Scrapper::~Scrapper() { curlpp::terminate(); }
void Scrapper::findTitle(const std::string& title) {
    curlpp::Easy request;
    request.setOpt(curlpp::Options::Url(
        "https://api.themoviedb.org/3/search/"
        "movie?api_key=749f20c38150f3dd95371aded810068b&language=en-US&query="
        "holidays&page=1&include_adult=false"));

    request.perform();
    std::cout << request << "\n";
}

}  // namespace themoviedb
}  // namespace kfl
