cmake_minimum_required(VERSION 3.0.0)
project(Trading_plateform VERSION 0.1.0)

include(CTest)
enable_testing()



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(FetchContent)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.7.3)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED) 
add_executable(Trading_plateform main.cpp)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(Trading_plateform PRIVATE ${CURL_LIBRARIES})