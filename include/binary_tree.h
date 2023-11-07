/*
 * Filename: binary_tree.h
 * Created on: May 12, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "binary_tree_excpt.h"
#include "node.h"
#include "queue_slkd.h"
#include "utils.h"

/**
 * @brief A binary tree data structure
 *
 * This class represents a binary tree that can store elements of type 'typeT'.
 * It allows for various operations related to binary trees, such as checking
 * if one node is an ancestor of another, and printing the tree's structure.
 *
 * @tparam typeT The type of elements stored in the binary tree
 */
template<typename typeT>
class BinaryTree
{
    private:
        dlkd::Node<typeT>* m_root;

        std::size_t m_numNodes;

        /**
         * @brief Recursively checks if node i is an ancestor of node j. Node i is
         * an ancestor of j if i is on the path from the root to j
         * @param node Pointer to the next node in the recursive call
         * @param i Key of the node
         * @param j Key of the node
         * @return True if i is an ancestor of j, False otherwise
         */
        bool IsAncestorRecursive(dlkd::Node<typeT>* node, typeT i, typeT j);

        /**
         * @brief Prints the tree
         * @param output File where the printing will be done
         * @param level Current node level
         * @param node Current node
         * @param side, should receive True if the node is on the left side, or False if
         * the node is on the right side
         */
        void DumpTree(dlkd::Node<typeT>*& node,
                      std::size_t         level,
                      const std::string&  vBar,
                      std::ofstream&      output,
                      bool                sideIsLeft);

        /**
         * @brief Insert a new element into the tree
         * @param key Key of the new node
         * @param node Pointer to the next node (recursive function)
         */
        void Insert(dlkd::Node<typeT>*& node, typeT key);

        /**
         * @brief Deletes the entire tree
         * @param node Current node to be deleted in each recursive function call
         */
        void DeleteTree(dlkd::Node<typeT>* node);

        /**
         * @brief Performs an in-order traversal on the tree
         * @param node Pointer to the next node
         * @param walk Queue where the traversal items will be stored
         */
        void InorderTreeWalk(slkd::Queue<typeT>& walk, dlkd::Node<typeT>* node);

        /**
         * @brief Performs a post-order traversal on the tree
         * @param node Pointer to the next node
         * @param walk Queue where the traversal items will be stored
         */
        void PostorderTreeWalk(slkd::Queue<typeT>& walk, dlkd::Node<typeT>* node);

        /**
         * @brief Performs a pre-order traversal on the tree
         * @param node Pointer to the next node
         * @param walk Queue where the traversal items will be stored
         */
        void PreorderTreeWalk(slkd::Queue<typeT>& walk, dlkd::Node<typeT>* node);

    public:
        BinaryTree();

        ~BinaryTree();

        /**
         * @brief Searches for a node with a specific key and returns a pointer to it
         * @param key Key being searched
         * @param node Pointer to the next node
         * @return Pointer to the node that contains the key, nullptr if there is no
         * node in the tree with this key
         */
        dlkd::Node<typeT>* Search(dlkd::Node<typeT>* node, typeT key);

        /**
         * @brief Overload for inserting a new element without the node pointer
         * @param key Key of the new node
         */
        void Insert(typeT key);

        /**
         * @brief Deletes a specific node
         * @param key Key of the node to be deleted
         */
        void DeleteNode(typeT key);

        /**
         * @brief Deletes the entire tree
         */
        void DeleteTree();

        /**
         * @brief Performs an in-order traversal on the tree
         * @param walk Queue where the traversal items will be stored
         */
        void InorderTreeWalk(slkd::Queue<typeT>& walk);

        /**
         * @brief Performs a pre-order traversal on the tree
         * @param walk Queue where the traversal items will be stored
         */
        void PreorderTreeWalk(slkd::Queue<typeT>& walk);

        /**
         * @brief Performs a post-order traversal on the tree
         * @param walk Queue where the traversal items will be stored
         */
        void PostorderTreeWalk(slkd::Queue<typeT>& walk);

        /**
         * @brief Performs a level-order traversal on the tree and prints the elements
         * as it goes
         */
        void LevelorderTreeWalk();

        /**
         * @brief Performs a level-order traversal on the tree
         * @param walk Queue where the traversal items will be stored
         */
        void LevelorderTreeWalk(slkd::Queue<typeT>& walk);

        /**
         * @brief Recursively checks if node i is an ancestor of node j. Node i is
         * an ancestor of j if i is on the path from the root to j
         * @param node Pointer to the next node in the recursive call
         * @param i Key of the node
         * @param j Key of the node
         * @return True if i is an ancestor of j, False otherwise
         */
        bool IsAncestorRecursive(typeT i, typeT j);

        /**
         * @brief Checks if node i is an ancestor of node j (uses only level-order
         * traversal)
         * @param i Key of the first node
         * @param j Key of the second node
         * @return True if i is an ancestor of j, False otherwise
         */

        bool IsAncestorLevelOrder(typeT i, typeT j);

        /**
         * @brief Checks if node i is an ancestor of node j (does not use level-order
         * traversal and is not a recursive solution)
         * @param i Key of the first node
         * @param j Key of the second node
         * @return True if i is an ancestor of j, False otherwise
         */
        bool IsAncestor(typeT i, typeT j);

        /**
         * @brief Returns the position (index) of an element in the array (needed for
         * the IsAncestor method)
         * @param array Search array
         * @param key Key to be searched
         * @return Integer corresponding to the index of the element in the array, -1 if
         * the element is not in the array
         */
        std::size_t KeyPosition(typeT (&array)[], int key);

        /**
         * @brief Inserts an already existing tree
         * @param root Pointer to the root of the tree to be stored
         * @param nodes Number of nodes in the tree
         * @throw bntexcpt::TreeIsNotEmpty If a tree is already stored
         * @throw bntexcpt::NewTreeIsEmpty If the tree to be inserted has no nodes
         */
        void InsertExistingTree(dlkd::Node<typeT>* root, int nodes);

        /**
         * @brief Prints the tree
         * @param output File where the printing will be done
         */
        void DumpTree(std::ofstream& output);
};

template<typename typeT>
BinaryTree<typeT>::BinaryTree()
{
    this->m_root     = nullptr;
    this->m_numNodes = 0;
}

template<typename typeT>
BinaryTree<typeT>::~BinaryTree()
{
    this->DeleteTree();
}

template<typename typeT>
dlkd::Node<typeT>* BinaryTree<typeT>::Search(dlkd::Node<typeT>* node, typeT key)
{
    if (node == nullptr or key == node->GetValue())
        return node;

    if (key < node->GetValue())
        return this->Search(node->GetLeftNode(), key);

    else
        return this->Search(node->GetRightNode(), key);
}

template<typename typeT>
void BinaryTree<typeT>::Insert(typeT key)
{
    if (this->m_root == nullptr)
    {
        this->m_root = new dlkd::Node<typeT>(key);
        this->m_numNodes++;
    }
    else
    {
        if (key < this->m_root->GetValue())
        {
            this->Insert(this->m_root->GetLeftNode(), key);
        }
        else
        {
            this->Insert(this->m_root->GetRightNode(), key);
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::Insert(dlkd::Node<typeT>*& node, typeT key)
{
    if (node == nullptr)
    {
        node = new dlkd::Node<typeT>(key);
        this->m_numNodes++;
    }
    else
    {
        if (key < node->GetValue())
        {
            this->Insert(node->GetLeftNode(), key);
        }
        else
        {
            this->Insert(node->GetRightNode(), key);
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::DeleteTree()
{
    this->DeleteTree(this->m_root);
    this->m_root = nullptr;
}

template<typename typeT>
void BinaryTree<typeT>::DeleteTree(dlkd::Node<typeT>* node)
{
    if (node != nullptr)
    {
        this->DeleteTree(node->GetLeftNode());
        this->DeleteTree(node->GetRightNode());
        delete node;
    }
}

template<typename typeT>
void BinaryTree<typeT>::InorderTreeWalk(slkd::Queue<typeT>& walk)
{
    if (this->m_root != nullptr)
    {
        this->InorderTreeWalk(walk, this->m_root->GetLeftNode());
        walk.Enqueue(this->m_root->GetValue());
        this->InorderTreeWalk(walk, this->m_root->GetRightNode());
    }
}

template<typename typeT>
void BinaryTree<typeT>::InorderTreeWalk(slkd::Queue<typeT>& walk,
                                        dlkd::Node<typeT>*  node)
{
    if (node != nullptr)
    {
        this->InorderTreeWalk(walk, node->GetLeftNode());
        walk.Enqueue(node->GetValue());
        this->InorderTreeWalk(walk, node->GetRightNode());
    }
}

template<typename typeT>
void BinaryTree<typeT>::PreorderTreeWalk(slkd::Queue<typeT>& walk)
{
    if (this->m_root != nullptr)
    {
        walk.Enqueue(this->m_root->GetValue());
        this->PreorderTreeWalk(walk, this->m_root->GetLeftNode());
        this->PreorderTreeWalk(walk, this->m_root->GetRightNode());
    }
}

template<typename typeT>
void BinaryTree<typeT>::PreorderTreeWalk(slkd::Queue<typeT>& walk,
                                         dlkd::Node<typeT>*  node)
{
    if (node != nullptr)
    {
        walk.Enqueue(node->GetValue());
        this->PreorderTreeWalk(walk, node->GetLeftNode());
        this->PreorderTreeWalk(walk, node->GetRightNode());
    }
}

template<typename typeT>
void BinaryTree<typeT>::PostorderTreeWalk(slkd::Queue<typeT>& walk)
{
    if (this->m_root != nullptr)
    {
        this->PostorderTreeWalk(walk, this->m_root->GetLeftNode());
        this->PostorderTreeWalk(walk, this->m_root->GetRightNode());
        walk.Enqueue(this->m_root->GetValue());
    }
}

template<typename typeT>
void BinaryTree<typeT>::PostorderTreeWalk(slkd::Queue<typeT>& walk,
                                          dlkd::Node<typeT>*  node)
{
    if (node != nullptr)
    {
        this->PostorderTreeWalk(walk, node->GetLeftNode());
        this->PostorderTreeWalk(walk, node->GetRightNode());
        walk.Enqueue(node->GetValue());
    }
}

template<typename typeT>
void BinaryTree<typeT>::LevelorderTreeWalk()
{
    slkd::Queue<dlkd::Node<typeT>*> queue;
    dlkd::Node<typeT>*              node;

    queue.Enqueue(this->m_root);

    while (not queue.IsEmpty())
    {
        node = queue.Dequeue();
        if (node != nullptr)
        {
            std::cout << node->GetValue() << " ";
            queue.Enqueue(node->GetLeftNode());
            queue.Enqueue(node->GetRightNode());
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::LevelorderTreeWalk(slkd::Queue<typeT>& walk)
{
    slkd::Queue<dlkd::Node<typeT>*> queue;
    dlkd::Node<typeT>*              node;

    queue.Enqueue(this->m_root);

    while (not queue.IsEmpty())
    {
        node = queue.Dequeue();
        if (node != nullptr)
        {
            walk.Enqueue(node->GetValue());
            queue.Enqueue(node->GetLeftNode());
            queue.Enqueue(node->GetRightNode());
        }
    }
}

template<typename typeT>
bool BinaryTree<typeT>::IsAncestorRecursive(typeT i, typeT j)
{
    if (this->m_root == nullptr)
        return false;

    if (i == this->m_root->GetValue())
        return true;

    if (j == this->m_root->GetValue())
        return false;

    if (i == j)
        return false;

    if (utils::Min(i, j) < this->m_root->GetValue() and
        utils::Max(i, j) > this->_root->key)
        return false;

    else if (i < this->m_root->GetValue() and j < this->_root->key)
        return this->IsAncestorRecursive(this->m_root->GetLeftNode(), i, j);
    else
        return this->IsAncestorRecursive(this->m_root->GetRightNode(), i, j);
}

template<typename typeT>
bool BinaryTree<typeT>::IsAncestorRecursive(dlkd::Node<typeT>* node, typeT i, typeT j)
{
    if (node == nullptr)
        return false;

    if (i == node->GetValue())
        return true;

    if (j == node->GetValue())
        return false;

    if (i == j)
        return false;

    if (utils::Min(i, j) < node->GetValue() and utils::Max(i, j) > node->key)
        return false;

    else if (i < node->GetValue() and j < node->key)
        return this->IsAncestorRecursive(node->GetLeftNode(), i, j);
    else
        return this->IsAncestorRecursive(node->GetRightNode(), i, j);
}

template<typename typeT>
bool BinaryTree<typeT>::IsAncestorLevelOrder(typeT i, typeT j)
{
    // A lógica por trás de usar somente level order é que ele organiza os valores no
    // array preservando a hierarquia da árvore de cima para baixo e do nó mais à
    // esquerda para o nó mais à direita. Por esse motivo, as mesmas verificações
    // realizadas no IsAncestorRecursive podem ser feitas no array (no caso, fila) que
    // armazena o caminhamento por nível

    int                root_aux;
    int                tmp;
    slkd::Queue<typeT> levelOrder;
    this->LevelorderTreeWalk(levelOrder);

    for (int k = 0; k < this->m_numNodes; k++)
    {
        if (k == 0)
        {
            try
            {
                root_aux = levelOrder.Dequeue();
            }
            catch (std::underflow_error& e)
            {
                std::cout << e.what() << std::endl;
                break;
            }
            if (i == root_aux)
            {
                return true;
            }
            continue;
        }
        if (i == j)
        {
            return false;
        }
        if (i == root_aux)
        {
            return true;
        }
        if (j == root_aux)
        {
            return false;
        }
        if (utils::Min(i, j) < root_aux and utils::Max(i, j) > root_aux)
        {
            return false;
        }
        else if (i < root_aux and j < root_aux)
        {
            try
            {
                do
                {
                    tmp = levelOrder.Dequeue();
                } while (tmp > root_aux);
                root_aux = tmp;
            }
            catch (std::underflow_error& e)
            {
                return false;
            }
        }
        else
        {
            try
            {
                do
                {
                    tmp = levelOrder.Dequeue();
                } while (tmp < root_aux);
                root_aux = tmp;
            }
            catch (std::underflow_error& e)
            {
                return false;
            }
        }
    }
    return false;
}

template<typename typeT>
std::size_t BinaryTree<typeT>::KeyPosition(typeT (&array)[], int key)
{
    for (int i = 0; i < this->m_numNodes; i++)
    {
        if (array[i] == key)
            return i;
    }
    return -1;
}

template<typename typeT>
bool BinaryTree<typeT>::IsAncestor(typeT i, typeT j)
{
    // Caso básico: i == j, então i não é ancestral de j
    if (i == j)
        return false;

    slkd::Queue<typeT> inorder, preorder, postorder;
    this->InorderTreeWalk(inorder);
    this->PreorderTreeWalk(preorder);
    this->PostorderTreeWalk(postorder);

    typeT inorderArray[this->m_numNodes];
    typeT preorderArray[this->m_numNodes];
    typeT postorderArray[this->m_numNodes];

    for (int i = 0; i < this->m_numNodes; i++)
    {
        inorderArray[i]   = inorder.Dequeue();
        preorderArray[i]  = preorder.Dequeue();
        postorderArray[i] = postorder.Dequeue();
    }

    int inorderPositionI = this->KeyPosition(inorderArray, i);
    int inorderPositionJ = this->KeyPosition(inorderArray, j);

    int inorderPositionRoot = this->KeyPosition(inorderArray, preorderArray[0]);

    // i < root < j  OU  j < root < i, implica em galhos diferentes o que é suficiente
    // para dizer que i não é ancestral de j No inorder é possível descobrir isso
    // comparando as posições relativas em relação a raiz
    if (utils::Min(inorderPositionI, inorderPositionJ) < inorderPositionRoot and
        utils::Max(inorderPositionI, inorderPositionJ) > inorderPositionRoot)
    {

        return false;
    }

    // i == raiz, então para todo j, i sempre será ancestral de j
    // da mesma maneira, se j == raiz, então para todo i, i nunca será ancestral de j
    if (inorderPositionI == inorderPositionRoot)
        return true;

    else if (inorderPositionJ == inorderPositionRoot)
        return false;

    int preorderPositionI = this->KeyPosition(preorderArray, i);
    int preorderPositionJ = this->KeyPosition(preorderArray, j);

    int postorderPositionI = this->KeyPosition(postorderArray, i);
    int postorderPositionJ = this->KeyPosition(postorderArray, j);

    // Verifica se i ou j não foi encontrado no array
    if (utils::Min(inorderPositionI,
                   inorderPositionJ,
                   preorderPositionI,
                   preorderPositionJ,
                   postorderPositionI,
                   postorderPositionJ) == -1)
    {

        return false;
    }

    return (postorderPositionI > postorderPositionJ and
            preorderPositionI < preorderPositionJ);
}

template<typename typeT>
void BinaryTree<typeT>::DumpTree(std::ofstream& output)
{
    int level = 0;

    if (this->m_root != nullptr)
    {
        output << this->m_root->GetValue();
        output << "(";
        output << level;
        output << ")" << std::endl;
        this->DumpTree(this->m_root->GetLeftNode(), level + 1, "", output, true);
        this->DumpTree(this->m_root->GetRightNode(), level + 1, "", output, false);
    }
}

template<typename typeT>
void BinaryTree<typeT>::InsertExistingTree(dlkd::Node<typeT>* root, int nodes)
{
    if (this->m_root != nullptr and this->m_numNodes == 0)
        throw bntexcpt::TreeIsNotEmpty();

    if (root == nullptr or nodes < 1)
        throw bntexcpt::NewTreeIsEmpty();

    this->m_numNodes = nodes + 1;
    this->m_root     = root;
}

template<typename typeT>
void BinaryTree<typeT>::DumpTree(dlkd::Node<typeT>*& node,
                                 std::size_t         level,
                                 const std::string&  vBar,
                                 std::ofstream&      output,
                                 bool                sideIsLeft)
{
    if (node != nullptr)
    {
        if (sideIsLeft)
        {
            output << vBar << "├───" << node->GetValue() << "(" << level << ")"
                   << std::endl;
        }
        else
        {
            output << vBar << "└───" << node->GetValue() << "(" << level << ")"
                   << std::endl;
        }
        this->DumpTree(node->GetLeftNode(),
                       level + 1,
                       vBar + (sideIsLeft ? "│    " : "     "),
                       output,
                       true);
        this->DumpTree(node->GetRightNode(),
                       level + 1,
                       vBar + (sideIsLeft ? "│    " : "     "),
                       output,
                       false);
    }
}

#endif // BINARY_TREE_H_
