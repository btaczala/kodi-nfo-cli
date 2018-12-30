#include "scrapper.h"
#include "scrapperbackend.h"
#include "themoviedb/tmdscrapper.h"

namespace kfl {
Scrapper::Scrapper() : d_ptr(std::make_unique<themoviedb::Scrapper>()) {}
Scrapper::~Scrapper() {}

void Scrapper::findTitle(const std::string& title) { d_ptr->findTitle(title); }
}  // namespace kfl
