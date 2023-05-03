cmake_minimum_required(VERSION 3.16)
project(chalchiu LANGUAGES CXX VERSION 2.3)

# --------------------------------------------------------------------------------------------------------
# Setup Cross-Compilation on Linux
# --------------------------------------------------------------------------------------------------------

if(NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    message(FATAL_ERROR "[${PROJECT_NAME}] Make sure to instruct cmake to use the toolchain file!")
endif()

# --------------------------------------------------------------------------------------------------------
# Create library
# --------------------------------------------------------------------------------------------------------

file(GLOB src "src/*.cpp")
file(GLOB exports "export/*")

add_library(${PROJECT_NAME} SHARED ${src} ${exports})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "iphlpapi")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)

if (MINGW)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-Wl,--enable-stdcall-fixup" -static -static-libgcc -static-libstdc++)
endif()

if (NOT MSVC AND NOT IS_CI)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -pedantic -pedantic-errors -Wfatal-errors)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wno-cast-function-type -Wno-missing-field-initializers)
endif()

# --------------------------------------------------------------------------------------------------------
# Generate "constants" file
# --------------------------------------------------------------------------------------------------------

configure_file("constants.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/private/constants.hpp")

# --------------------------------------------------------------------------------------------------------
# Include directories
# --------------------------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PUBLIC  "include")
target_include_directories(${PROJECT_NAME} PRIVATE "include/chalchiu" "private")

# --------------------------------------------------------------------------------------------------------
# Link Dependencies and Add Sources
# --------------------------------------------------------------------------------------------------------

include("cmake/cpm.cmake")

find_package(Lua REQUIRED)

CPMAddPackage("gh:ThePhD/sol2@3.3.0")
CPMAddPackage("gh:curve/lime#0a5f62f")
CPMAddPackage("gh:gabime/spdlog@1.11.0")

target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC sol2 spdlog lime ${LUA_LIBRARIES})