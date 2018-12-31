add_library(themoviedb-backend
            STATIC
            themoviedb/config.cpp
            themoviedb/tmdscrapper.cpp)
target_include_directories(themoviedb-backend
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(themoviedb-backend PUBLIC fmt json curl_backend MetaStuff)

add_library(nfo_core STATIC scrapper.cpp)
target_include_directories(nfo_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(nfo_core PUBLIC themoviedb-backend)
