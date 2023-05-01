#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>

#include "doctest.h"
#include "list_doubly_linked.hh"
#include "list_excpt.hh"

TEST_CASE("Remover elemento") {
    dlkd::List<int> list;

    SUBCASE("Remover algo de uma lista vazia") {
        list.remove(1);
        CHECK(list.size() == 0);
    }

    SUBCASE("Remover 1 elemento") {
        list.push_back(1);
        CHECK(list.size() == 1);
        list.remove(1);
        CHECK(list.size() == 0);
    }

    SUBCASE("Remover 2 elemento") {
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
        CHECK(list.size() == 4);
        list.remove(2);
        CHECK(list.size() == 3);
        list.remove(4);
        CHECK(list.size() == 2);
    }
}

TEST_CASE("Primeiro e último elemento") {
    dlkd::List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.remove(1);
    CHECK(list.front() == 2);
    CHECK(list.back() == 4);
}

TEST_CASE("Limpar lista e excessões") {
    dlkd::List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.clean();
    CHECK_THROWS_AS(list.front(), lstexcpt::ListIsEmpty);
    CHECK_THROWS_AS(list.back(), lstexcpt::ListIsEmpty);
    CHECK_THROWS_AS(list.print(), lstexcpt::ListIsEmpty);
}
