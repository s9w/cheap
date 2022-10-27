#include "doctest.h"
#include "../cheap.h"

using namespace cheap::literals;

TEST_CASE("literal namespace") {
   const auto x = "xyz"_att;
}
