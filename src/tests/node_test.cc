/*
 * Filename: node_test.cc
 * Created on: November  3, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"
#include "node.h"
#include <cmath>
#include <cstdint>

TEST_CASE("slkd::Node Tests")
{
    slkd::Node<uint32_t> node1(10);
    slkd::Node<uint32_t> node2(20);
    slkd::Node<uint32_t> node3(30, &node2);

    // Test SetKey and GetKey
    node1.SetValue(42);
    CHECK(node1.GetValue() == 42);

    // Test SetNextNode and GetNextNode
    node1.SetNextNode(&node2);
    CHECK(node1.GetNextNode() == &node2);

    node2.SetNextNode(&node3);
    CHECK(node2.GetNextNode() == &node3);
}

TEST_CASE("dlkd::Node Tests")
{
    dlkd::Node<double_t> node1(3.14);
    dlkd::Node<double_t> node2(2.71);
    dlkd::Node<double_t> node3(1.618, &node1, &node2);

    // Test SetKey and GetKey
    node1.SetValue(2.718);
    CHECK(node1.GetValue() == 2.718);

    // Test SetLeftNode and GetLeftNode
    node2.SetLeftNode(&node3);
    CHECK(node2.GetLeftNode() == &node3);

    // Test SetRightNode and GetRightNode
    node1.SetRightNode(&node2);
    CHECK(node1.GetRightNode() == &node2);
}
