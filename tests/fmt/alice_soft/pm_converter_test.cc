#include "fmt/alice_soft/pm_converter.h"
#include "test_support/catch.hh"
#include "test_support/file_support.h"
#include "test_support/image_support.h"

using namespace au;
using namespace au::fmt::alice_soft;

static void do_test(
    const std::string &input_path, const std::string &expected_path)
{
    PmConverter converter;
    auto input_file = tests::file_from_path(input_path);
    auto expected_image = tests::image_from_path(expected_path);
    auto actual_image = tests::image_from_file(*converter.decode(*input_file));
    tests::compare_images(*expected_image, *actual_image);
}

TEST_CASE("AliceSoft PM 8-bit images", "[fmt]")
{
    do_test(
        "tests/fmt/alice_soft/files/pm/CG40000.pm",
        "tests/fmt/alice_soft/files/pm/CG40000-out.png");
}

TEST_CASE("AliceSoft PM 16-bit images with transparency", "[fmt]")
{
    do_test(
        "tests/fmt/alice_soft/files/pm/G006.PMS",
        "tests/fmt/alice_soft/files/pm/G006-out.png");
}

TEST_CASE("AliceSoft PM 16-bit images without transparency", "[fmt]")
{
    do_test(
        "tests/fmt/alice_soft/files/pm/G214.PMS",
        "tests/fmt/alice_soft/files/pm/G214-out.png");
}

TEST_CASE("AliceSoft PM 8-bit images with inverted channels", "[fmt]")
{
    do_test(
        "tests/fmt/alice_soft/files/pm/ALCG0016.PMS",
        "tests/fmt/alice_soft/files/pm/ALCG0016-out.png");
}
