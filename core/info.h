#ifndef INFO_H_TZCHDXLS
#define INFO_H_TZCHDXLS

#include <cstdint>
#include <string>

namespace kfl {
struct Info {
    std::uint32_t id;
    std::string title;
    std::string releaseDate;
    double popularity;
};

struct FullMovieEntry {
    std::uint32_t id;
    std::string title;
    std::string tagline;
    std::string overview;
    std::string release_date;
};
}  // namespace kfl

#endif /* end of include guard: INFO_H_TZCHDXLS */
