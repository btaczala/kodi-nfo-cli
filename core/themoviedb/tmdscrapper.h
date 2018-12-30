
#ifndef TMDSCRAPPER_H_N0R6FHDM
#define TMDSCRAPPER_H_N0R6FHDM

#include "scrapperbackend.h"
#include <curlpp/cURLpp.hpp>

namespace kfl {
namespace themoviedb {
struct Scrapper : public kfl::ScrapperBackend {
    Scrapper();
    ~Scrapper();
    void findTitle(const std::string& title) override;
};
}  // namespace themoviedb
}  // namespace kfl

#endif /* end of include guard: TMDSCRAPPER_H_N0R6FHDM */

