cmake_minimum_required(VERSION 2.8.12)

set(OCTASPIRE_SDL2_UTILS_CONFIG_VERSION_MAJOR 0)
set(OCTASPIRE_SDL2_UTILS_CONFIG_VERSION_MINOR 4)
set(OCTASPIRE_SDL2_UTILS_CONFIG_VERSION_PATCH 0)

set(OCTASPIRE_SDL2_UTILS_CONFIG_TEST_RES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test/resource/")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/octaspire/sdl2-utils/octaspire_sdl2_utils_config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/octaspire/sdl2-utils/octaspire_sdl2_utils_config.h")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel. " FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(EXISTS "${CMAKE_SOURCE_DIR}/.gitmodules")
    message("== Updating git submodules...")
    execute_process(
        COMMAND git submodule update --init --recursive --remote
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()


project(octaspire-sdl2-utils C)
message("== Build type is ${CMAKE_BUILD_TYPE}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/external/cmake")

find_package(SDL2       REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

if (NOT TARGET octaspire_core)
    add_subdirectory(external/octaspire_core)
endif()

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/octaspire/sdl2-utils/*.h")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_core/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_core/build/include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")


option(OCTASPIRE_SDL2_UTILS_COVERAGE "OCTASPIRE_SDL2_UTILS_COVERAGE" OFF)

if(OCTASPIRE_SDL2_UTILS_COVERAGE)
    message("== Code coverage enabled")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif(OCTASPIRE_SDL2_UTILS_COVERAGE)

add_library(octaspire-sdl2-utils STATIC ${SOURCES})
set_property(TARGET octaspire-sdl2-utils PROPERTY C_STANDARD 99)
set_property(TARGET octaspire-sdl2-utils PROPERTY C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c99 -fno-omit-frame-pointer -Wall -Wextra -pedantic -Werror")
endif(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
    #set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fcolor-diagnostics -fsanitize=undefined")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fcolor-diagnostics")
endif(CMAKE_C_COMPILER_ID MATCHES "Clang")

target_link_libraries(octaspire-sdl2-utils ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} octaspire_core m)
install(TARGETS octaspire-sdl2-utils DESTINATION bin)

add_custom_target(
    cppcheck-sdl2-utils
    COMMAND cppcheck --std=c99 -I "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_core/include" "${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_core/include"
            --enable=warning,performance,portability
            --verbose --quiet ${SOURCES} ${HEADERS})

add_custom_target(
    vera-sdl2-utils
    COMMAND vera++ --error ${SOURCES} ${HEADERS})

enable_testing()
include(CTest)
add_subdirectory(test)

