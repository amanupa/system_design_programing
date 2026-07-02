cmake_minimum_required(VERSION 3.16)

project(ParkingManagementSystem
    VERSION 0.1.0
    DESCRIPTION "Production-quality Parking Management System (Modern C++20)"
    LANGUAGES CXX)

# ----------------------------------------------------------------------------
# Global standards
# ----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Treat warnings seriously; this is "production" code.
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ----------------------------------------------------------------------------
# Core library (all reusable logic). The app and the tests both link this.
# Sources are globbed for convenience while the project grows; CONFIGURE_DEPENDS
# re-globs on rebuild so new .cpp files are picked up automatically.
# ----------------------------------------------------------------------------
file(GLOB_RECURSE PMS_CORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp")
# The executable's own translation unit must not be part of the library.
list(REMOVE_ITEM PMS_CORE_SOURCES "${CMAKE_SOURCE_DIR}/src/app/main.cpp")

add_library(pms_core STATIC ${PMS_CORE_SOURCES})
target_include_directories(pms_core PUBLIC "${CMAKE_SOURCE_DIR}/src")

# ----------------------------------------------------------------------------
# Application executable
# ----------------------------------------------------------------------------
add_executable(pms src/app/main.cpp)
target_link_libraries(pms PRIVATE pms_core)

# ----------------------------------------------------------------------------
# Tests (GoogleTest) — enabled once the tests/ tree exists (Phase 15).
# ----------------------------------------------------------------------------
enable_testing()
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()
