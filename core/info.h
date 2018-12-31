#ifndef INFO_H_TZCHDXLS
#define INFO_H_TZCHDXLS

#include <cstdint>
#include <string>

namespace kfl {
struct Info {
    std::uint32_t id;
    std::string title;
    std::string release_date;
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

#include "Meta.h"

namespace meta {
template <>
inline auto registerMembers<kfl::Info>() {
    return members(member("id", &kfl::Info::id),
                   member("title", &kfl::Info::title),
                   member("release_date", &kfl::Info::release_date),
                   member("popularity", &kfl::Info::popularity));
}
template <>
inline auto registerMembers<kfl::FullMovieEntry>() {
    return members(member("id", &kfl::FullMovieEntry::id),
                   member("title", &kfl::FullMovieEntry::title),
                   member("tagline", &kfl::FullMovieEntry::tagline),
                   member("overview", &kfl::FullMovieEntry::overview),
                   member("release_date", &kfl::FullMovieEntry::release_date));
}
}  // namespace meta

#endif /* end of include guard: INFO_H_TZCHDXLS */
