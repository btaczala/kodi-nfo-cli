
#ifndef TMDSCRAPPER_H_N0R6FHDM
#define TMDSCRAPPER_H_N0R6FHDM

#include <curlpp/cURLpp.hpp>
#include "scrapperbackend.h"

namespace kfl {
namespace themoviedb {
struct Scrapper : public kfl::ScrapperBackend {
    Scrapper();
    ~Scrapper();
    std::vector<Info> findTitle(const QueryOptions& title) override;
};
}  // namespace themoviedb
}  // namespace kfl

#endif /* end of include guard: TMDSCRAPPER_H_N0R6FHDM */

