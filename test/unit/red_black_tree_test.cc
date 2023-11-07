/*
* Filename: red_black_tree_test.cc
* Created on: July  7, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "doctest.h"

#include "red_black_tree.h"

TEST_CASE("Inserção") {
    rbtree::RedBlackTree<int> tree;

    tree.Insert(5);
    tree.Insert(2);
    tree.Insert(8);
    tree.Insert(1);
    tree.Insert(4);
    tree.Insert(7);
    tree.Insert(10);

    CHECK(tree.Size() == 7);
    CHECK(tree.IsRedBlackTreeBalanced());
}

TEST_CASE("Balancemaneto: Caso árvore degenerada") {
    rbtree::RedBlackTree<int> tree;

    tree.Insert(0);
    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(4);
    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(10);
    tree.Insert(22);
    tree.Insert(33);
    tree.Insert(83);
    tree.Insert(102);

    CHECK(tree.IsRedBlackTreeBalanced());
}

TEST_CASE("Remoção") {
    rbtree::RedBlackTree<int> tree;

    tree.Insert(5);
    tree.Insert(2);
    tree.Insert(8);
    tree.Insert(1);
    tree.Insert(6);
    tree.Insert(4);
    tree.Insert(7);
    tree.Insert(10);

    tree.Remove(4);
    CHECK(tree.Size() == 7);

    tree.Remove(10);
    CHECK(tree.Size() == 6);

    // Remover elemento que não está na árvore
    tree.Remove(10);
    CHECK(tree.Size() == 6);
}

TEST_CASE("Esvaziamento do tree") {
    rbtree::RedBlackTree<int> tree;

    CHECK(tree.Size() == 0);
    CHECK(tree.IsEmpty());

    tree.Insert(5);
    tree.Insert(2);
    tree.Insert(8);
    tree.Insert(1);
    tree.Insert(4);
    tree.Insert(7);
    tree.Insert(10);

    tree.Clear();

    CHECK(tree.Size() == 0);
    CHECK(tree.IsEmpty());
}
