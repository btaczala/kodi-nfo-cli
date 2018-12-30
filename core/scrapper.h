#ifndef SCRAPPER_H_WZM85IKR
#define SCRAPPER_H_WZM85IKR

#include <memory>
#include <string>

namespace kfl {

struct ScrapperBackend;
struct Scrapper {
    Scrapper();
    ~Scrapper();
    void findTitle(const std::string& title);

   private:
    std::unique_ptr<ScrapperBackend> d_ptr;
};
};  // namespace kfl

#endif /* end of include guard: SCRAPPER_H_WZM85IKR */
