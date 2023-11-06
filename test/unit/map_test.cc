/*
 * Filename: map_test.cc
 * Created on: June 28, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"
#include "map.h"
#include <cstdint>

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

    CHECK(map[5] == "Five");
    CHECK(map[2] == "Two");
    CHECK(map[8] == "Eight");
    CHECK(map[1] == "One");
    CHECK(map[4] == "Four");
    CHECK(map[7] == "Seven");
    CHECK(map[10] == "Ten");
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

    map.Clear();
    CHECK(map.Size() == 0);
    CHECK(map.IsEmpty());
}

// TODO: Corrigir: Em alguns casos de acesso com o operador [], caso a chave ainda não
// exista, ocorre o erro de segmentação
TEST_CASE("Incremento")
{
    rbtree::Map<char, uint32_t> map;

    std::string palavra = "PARDSCDACACMZNSDI@!*@#";

    for (char& letra : palavra)
    {
        if (map.Contains(letra))
            map[letra]++;
        else
            map[letra];
    }

    map.Clear();
    CHECK(map.Size() == 0);
    CHECK(map.IsEmpty());
}
