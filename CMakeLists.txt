cmake_minimum_required(VERSION 3.20)
project(depsort VERSION 0.1.0 LANGUAGES CXX)

# --- Global settings ---------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # lets clangd / clang-tidy understand the project

# CMake 4.x refuses dependencies that declare very old minimum versions.
# This keeps FetchContent dependencies building without errors.
set(CMAKE_POLICY_VERSION_MINIMUM 3.10)

option(DEPSORT_BUILD_TESTS "Build unit tests" ON)
option(DEPSORT_SANITIZERS "Enable AddressSanitizer + UBSan (Debug builds)" OFF)

# --- Dependencies (downloaded automatically, nothing to install) ------------
include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.4.2
  GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(nlohmann_json CLI11)

# --- Warnings helper ---------------------------------------------------------
function(depsort_set_warnings target)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 /WX)
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror)
  endif()
  if(DEPSORT_SANITIZERS AND NOT MSVC)
    target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(${target} PRIVATE -fsanitize=address,undefined)
  endif()
endfunction()

# --- Core library: all the real logic lives here -----------------------------
add_library(depsort_core
  src/package.cpp)
target_include_directories(depsort_core PUBLIC include)
target_link_libraries(depsort_core PUBLIC nlohmann_json::nlohmann_json)
depsort_set_warnings(depsort_core)

# --- Command-line tool: thin wrapper around the library ----------------------
add_executable(depsort src/main.cpp)
target_link_libraries(depsort PRIVATE depsort_core CLI11::CLI11)
depsort_set_warnings(depsort)

# --- Tests -------------------------------------------------------------------
if(DEPSORT_BUILD_TESTS)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
    GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(Catch2)

  enable_testing()
  add_executable(depsort_tests tests/test_package.cpp)
  target_link_libraries(depsort_tests PRIVATE depsort_core Catch2::Catch2WithMain)
  depsort_set_warnings(depsort_tests)

  include(Catch)
  catch_discover_tests(depsort_tests)
endif()
