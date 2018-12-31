
add_library(cxxopts INTERFACE)
target_include_directories(cxxopts INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/cxxopts)

add_library(json INTERFACE)
target_include_directories(json INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/json)

add_subdirectory(fmt)
add_subdirectory(curlpp)

add_library(curl_backend INTERFACE)
target_link_libraries(curl_backend INTERFACE curlpp)
target_include_directories(curl_backend INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/curlpp/include)

add_library(MetaStuff INTERFACE)
target_include_directories(MetaStuff INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/MetaStuff/include)
