cmake_minimum_required(VERSION 3.20)
project(benchmark-cpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# cpp-httplib 다운로드
include(FetchContent)
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG v0.14.3
)
FetchContent_MakeAvailable(httplib)

# nlohmann/json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

# 헤더 경로 추가
include_directories(src)
include_directories(${httplib_SOURCE_DIR})

add_executable(benchmark-cpp src/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(benchmark-cpp 
    Threads::Threads 
    nlohmann_json::nlohmann_json
)

target_compile_options(benchmark-cpp PRIVATE -O3)