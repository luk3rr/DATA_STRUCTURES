/*
 * Filename: map_test.cc
 * Created on: June 28, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cstdint>

#include "doctest.h"

#include "map.h"

TEST_CASE("Inserção e busca")
{
    rbtree::Map<uint32_t, std::string> map;

    map.Insert(5, "Five");
    map.Insert(2, "Two");
    map.Insert(8, "Eight");
    map.Insert(1, "One");
    map.Insert(4, "Four");
    map.Insert(7, "Seven");
    map.Insert(10, "Ten");

    CHECK(map.Size() == 7);

    SUBCASE("With [] operator")
    {
        CHECK(map[5] == "Five");
        CHECK(map[2] == "Two");
        CHECK(map[8] == "Eight");
        CHECK(map[1] == "One");
        CHECK(map[4] == "Four");
        CHECK(map[7] == "Seven");
        CHECK(map[10] == "Ten");
    }

    SUBCASE("With At() method")
    {
        CHECK(map.At(5) == "Five");
        CHECK(map.At(2) == "Two");
        CHECK(map.At(8) == "Eight");
        CHECK(map.At(1) == "One");
        CHECK(map.At(4) == "Four");
        CHECK(map.At(7) == "Seven");
        CHECK(map.At(10) == "Ten");
    }
}

TEST_CASE("Remoção")
{
    rbtree::Map<uint32_t, std::string> map;

    map.Insert(5, "Five");
    map.Insert(2, "Two");
    map.Insert(8, "Eight");
    map.Insert(1, "One");
    map.Insert(4, "Four");
    map.Insert(7, "Seven");
    map.Insert(10, "Ten");

    map.Remove(4);
    CHECK(map.Size() == 6);
    CHECK(not map.Contains(4));
    map.Remove(6);
    CHECK(not map.Contains(6));
}

TEST_CASE("Esvaziamento do map")
{
    rbtree::Map<uint32_t, std::string> map;

    CHECK(map.Size() == 0);
    CHECK(map.IsEmpty());
    CHECK(not map.Contains(5));
    CHECK(map[5] == ""); //

    map.Insert(5, "Five");
    map.Insert(2, "Two");
    map.Insert(8, "Eight");
    map.Insert(1, "One");
    map.Insert(4, "Four");
    map.Insert(7, "Seven");
    map.Insert(10, "Ten");

    map.Clear();

    CHECK(map.Size() == 0);
    CHECK(map.IsEmpty());
}

TEST_CASE("Mudar valores")
{
    rbtree::Map<uint32_t, std::string> map;

    map.Insert(5, "Five");
    map.Insert(2, "Two");
    map.Insert(8, "Eight");
    map.Insert(1, "One");
    map.Insert(4, "Four");
    map.Insert(7, "Seven");
    map.Insert(10, "Ten");

    for (rbtree::Map<uint32_t, std::string>::Iterator it = map.begin(); it != map.end();
         ++it)
    {
        it->GetValue().SetSecond("");
    }

    CHECK(map[4] == "");

    for (auto& pair : map)
    {
        pair.SetSecond("Allow");
    }

    CHECK(map[5] == "Allow");

    // At()
    map.At(5) = "Five";
    CHECK(map[5] == "Five");

    map.Clear();
    CHECK(map.Size() == 0);
    CHECK(map.IsEmpty());
}

TEST_CASE("Incremento")
{
    rbtree::Map<char, uint32_t> map;

    std::string palavra = "PARDSDDABACMZNSDI@!*@#";

    for (char& letra : palavra)
    {
        map[letra]++;
    }

    map.Clear();
    CHECK(map.Size() == 0);
    CHECK(map.IsEmpty());
}
