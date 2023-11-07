/*
 * Filename: node_rbtree_test.cc
 * Created on: November  3, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cmath>
#include <cstdint>

#include "doctest.h"

#include "node_rbtree.h"
#include "pair.h"

TEST_CASE("rbtree::Node Tests")
{
    SUBCASE("Test SetValue and GetValue")
    {
        rbtree::Node<Pair<uint32_t, double_t>> node(Pair<uint32_t, double_t>(42, 3.14));
        CHECK(node.GetValue().GetFirst() == 42);
        CHECK(node.GetValue().GetSecond() == 3.14);

        node.SetValue(Pair<uint32_t, double_t>(10, 2.71));
        CHECK(node.GetValue().GetFirst() == 10);
        CHECK(node.GetValue().GetSecond() == 2.71);
    }

    SUBCASE("Test SetColor and GetColor")
    {
        rbtree::Node<Pair<uint32_t, double_t>> node(Pair<uint32_t, double_t>(42, 3.14));
        CHECK(node.GetColor() == rbtree::Color::RED);

        node.SetColor(rbtree::BLACK);
        CHECK(node.GetColor() == rbtree::Color::BLACK);
    }

    SUBCASE("Test SetParent and GetParent")
    {
        rbtree::Node<Pair<int32_t, double_t>> node1(Pair<int32_t, double_t>(-42, 3.14));
        rbtree::Node<Pair<int32_t, double_t>> node2(Pair<int32_t, double_t>(-10, 2.71));
        node1.SetParent(&node2);

        CHECK(node1.GetParent() == &node2);
    }
}
