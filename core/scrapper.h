#ifndef SCRAPPER_H_WZM85IKR
#define SCRAPPER_H_WZM85IKR

#include <memory>
#include <string>
#include <vector>

#include "info.h"
#include "queryoptions.h"

namespace kfl {

struct ScrapperBackend;
struct Scrapper {
    Scrapper();
    ~Scrapper();
    std::vector<Info> findTitle(const QueryOptions& opts);
    FullMovieEntry get(const std::uint32_t& id);

   private:
    std::unique_ptr<ScrapperBackend> d_ptr;
};
};  // namespace kfl

#endif /* end of include guard: SCRAPPER_H_WZM85IKR */
