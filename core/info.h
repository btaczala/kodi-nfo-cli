#ifndef INFO_H_TZCHDXLS
#define INFO_H_TZCHDXLS

#include <string>
#include <cstdint>

namespace kfl {
struct Info {
    std::uint32_t id;
    std::string title;
    std::string releaseDate;
    double popularity;
};
}  // namespace kfl

#endif /* end of include guard: INFO_H_TZCHDXLS */
