#include "depsort/package.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("library reports its version") {
    REQUIRE(depsort::version() == "0.1.0");
}

// Next tests to write (one per feature, before or alongside the code):
//  - load_packages parses a valid file
//  - load_packages rejects malformed JSON with a clear error
//  - sort puts B before A when A requires B
//  - requirements outside the input list are ignored
//  - a cycle A -> B -> A is detected and the path is reported
//  - "required by" lists every package that needs a given one
