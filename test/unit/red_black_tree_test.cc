/*
 * Filename: red_black_tree_test.cc
 * Created on: July  7, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include <random>
#include <set>

#include "red_black_tree.h"
#include "vector.h"

TEST_CASE("Inserção")
{
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

TEST_CASE("Balancemaneto: Caso árvore degenerada")
{
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

TEST_CASE("Remoção")
{
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

TEST_CASE("Esvaziamento do tree")
{
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

TEST_CASE("Insertion and Removal")
{
    rbtree::RedBlackTree<int>        tree;
    std::random_device               rd;
    std::mt19937                     gen(rd());
    std::uniform_real_distribution<> probability(0.0, 1.0);

    std::set<int> valuesInTree;

    const int numOperations = 30;

    for (int i = 0; i < numOperations; ++i)
    {
        double choice = probability(gen);

        Vector<int> insertionValues;
        Vector<int> removalValues;

        if (choice < 0.75)
        {
            // 75% of chance of adding
            int value = i;
            tree.Insert(value);
            valuesInTree.insert(value);
            insertionValues.PushBack(value);
        }
        else
        {
            // 25% of chance of removing
            if (not valuesInTree.empty())
            {
                std::uniform_int_distribution<> dis(0, valuesInTree.size() - 1);
                auto                            it = valuesInTree.begin();
                std::advance(it, dis(gen));
                int value = *it;
                tree.Remove(value);
                valuesInTree.erase(it);
                removalValues.PushBack(value);
            }
        }
    }

    // Check if the tree is balanced
    CHECK(tree.IsRedBlackTreeBalanced());
}
