#ifndef SCRAPPERBACKEND_H_RHLQ5SVR
#define SCRAPPERBACKEND_H_RHLQ5SVR

#include <string>

namespace kfl {
struct ScrapperBackend {
    virtual ~ScrapperBackend() = default;
    virtual void findTitle(const std::string& title) = 0;
};
}  // namespace kfl

#endif /* end of include guard: SCRAPPERBACKEND_H_RHLQ5SVR */
