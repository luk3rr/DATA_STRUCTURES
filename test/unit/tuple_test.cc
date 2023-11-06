/*
 * Filename: tuple_test.cc
 * Created on: October 29, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include "tuple.h"
#include <string>

TEST_CASE("Tuple with two elements")
{
    Tuple<int, double> tuple(42, 3.14);

    SUBCASE("Check the first element")
    {
        CHECK(Get<0>(tuple) == 42);
    }

    SUBCASE("Check the second element")
    {
        CHECK(Get<1>(tuple) == 3.14);
    }
}

TEST_CASE("Tuple with three elements")
{
    Tuple<char, int, std::string> tuple('A', 123, "Hello");

    SUBCASE("Check the third element")
    {
        CHECK(Get<2>(tuple) == "Hello");
    }

    SUBCASE("Check the first element")
    {
        CHECK(Get<0>(tuple) == 'A');
    }

    SUBCASE("Check the second element")
    {
        CHECK(Get<1>(tuple) == 123);
    }
}

TEST_CASE("Tuple with one element")
{
    Tuple<std::string> tuple("Single Element");

    CHECK(Get<0>(tuple) == "Single Element");
}
