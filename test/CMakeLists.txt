cmake_minimum_required(VERSION 2.8.12)
project(octaspire-sdl2-utils-test-runner C)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resource" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
file(GLOB SOURCES "*.c")
include_directories(${CMAKE_SOURCE_DIR})
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c11 -Wall -Wextra -pedantic -Werror")
endif(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")

if(OCTASPIRE_sdl2-utils_COVERAGE)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif(OCTASPIRE_sdl2-utils_COVERAGE)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} octaspire-core)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
