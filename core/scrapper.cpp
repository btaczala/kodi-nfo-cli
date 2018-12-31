#include "scrapper.h"
#include "scrapperbackend.h"
#include "themoviedb/tmdscrapper.h"

namespace kfl {
Scrapper::Scrapper() : d_ptr(std::make_unique<themoviedb::Scrapper>()) {}
Scrapper::~Scrapper() {}

std::vector<Info> Scrapper::findTitle(const QueryOptions& title) { return d_ptr->findTitle(title); }
FullMovieEntry Scrapper::get(const std::uint32_t& id) { return d_ptr->get(id); }
}  // namespace kfl
