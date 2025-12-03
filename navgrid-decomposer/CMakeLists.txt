cmake_minimum_required(VERSION 3.20)
project(navgrid-decomposer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.0
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(navgrid-decomposer
    navgrid-decomposer.cpp
    ${APP_SOURCES}
)

target_include_directories(navgrid-decomposer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(navgrid-decomposer PRIVATE raylib)

if (MSVC)
  target_compile_options(navgrid-decomposer PRIVATE /W4 /permissive-)
else()
  target_compile_options(navgrid-decomposer PRIVATE -Wall -Wextra -Wpedantic)
endif()
