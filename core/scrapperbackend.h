#ifndef SCRAPPERBACKEND_H_RHLQ5SVR
#define SCRAPPERBACKEND_H_RHLQ5SVR

#include <string>
#include "info.h"
#include "queryoptions.h"

namespace kfl {
struct ScrapperBackend {
    virtual ~ScrapperBackend() = default;
    virtual std::vector<Info> findTitle(const QueryOptions& title) = 0;
};
}  // namespace kfl

#endif /* end of include guard: SCRAPPERBACKEND_H_RHLQ5SVR */
