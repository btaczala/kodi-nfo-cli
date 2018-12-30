find_package(CURLpp REQUIRED)
message(STATUS "Curlpp ${CURLPP_INCLUDE_DIRS}")
add_library(themoviedb-backend
            STATIC
            themoviedb/config.cpp
            themoviedb/tmdscrapper.cpp)
target_include_directories(themoviedb-backend
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                  ${CURLPP_INCLUDE_DIR})
target_link_libraries(themoviedb-backend PUBLIC ${CURLPP_LIBRARIES} fmt)

add_library(nfo_core STATIC scrapper.cpp)
target_include_directories(nfo_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(nfo_core PUBLIC themoviedb-backend)
