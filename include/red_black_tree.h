/*
 * Filename: red_black_tree.h
 * Created on: July  7, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include <cstddef>
#include <fstream>
#include <iostream>

#include "node_rbtree.h"
#include "utils.h"

namespace rbtree
{
    /**
     * @brief A Red-Black Tree data structure class
     *
     * This class represents a Red-Black Tree, a type of self-balancing binary search
     * tree. It is designed to efficiently store and manage elements of type 'typeT'
     *
     * Time Complexity:
     *   Function       Worst case      Amortized
     *    insert         O(log n)         O(1)
     *    delete         O(log n)         O(1)
     *    search         O(log n)       O(log n)
     *
     * Space Complexity: O(n)
     *
     * @tparam typeT The type of elements stored in the Red-Black Tree
     * @tparam lessComparator The custom comparator for less-than comparisons
     * @tparam equalComparator The custom comparator for equal comparisons
     */
    template<typename typeT,
             typename lessComparator  = utils::less<typeT>,
             typename equalComparator = utils::equal<typeT>>
    class RedBlackTree
    {
        protected:
            Node<typeT>* m_root;     // Pointer to the root node
            std::size_t  m_numNodes; // Total number of nodes in the tree

            // Custom comparators
            lessComparator  m_lessComp;
            equalComparator m_equalComp;

            /**
             * @brief Insert a new key-value pair into the Red-Black Tree.
             * @param parent The parent node of the current recursive call.
             * @param node The current node in the recursive call.
             * @param key The key to be stored.
             * @return Pointer to the new node that was inserted.
             */
            Node<typeT>*
            Insert(Node<typeT>* parent, Node<typeT>*& node, const typeT& key);

            /**
             * @brief Corrects the Red-Black Tree properties after an insertion.
             * @param node The node that was inserted.
             */
            void FixInsert(Node<typeT>* node);

            /**
             * @brief Delete a specific node
             * @param node The node to be deleted
             */
            void DeleteNode(Node<typeT>* node);

            /**
             * @brief Corrects the Red-Black Tree properties after a deletion
             * @param node The node from which the correction will start
             */
            void FixDelete(Node<typeT>* node);

            /**
             * @brief Transplants one node with another
             * @param node1 The first node
             * @param node2 The second node
             */
            void Transplant(Node<typeT>*& node1, Node<typeT>*& node2);

            /**
             * @brief Search for the node containing a specific key
             * @param node The current node in the recursive call
             * @param key The key used in the search
             * @return Pointer to the node or nullptr if the node was not found
             */
            Node<typeT>* Search(Node<typeT>* node, const typeT& key);

            /**
             * @brief Perform a left rotation
             * @param node The node to be rotated
             * @return Pointer to the node that takes the place of the rotated node
             */
            Node<typeT>* RotateLeft(Node<typeT>* node);

            /**
             * @brief Perform a right rotation
             * @param node The node to be rotated
             * @return Pointer to the node that takes the place of the rotated node
             */
            Node<typeT>* RotateRight(Node<typeT>* node);

            /**
             * @brief Move a red node to the left
             * @param node The node to be moved
             * @return Pointer to the node that takes the place of the moved node
             */
            Node<typeT>* MoveRed2Left(Node<typeT>* node);

            /**
             * @brief Move a red node to the right
             * @param node The node to be moved
             * @return Pointer to the node that takes the place of the moved node
             */
            Node<typeT>* MoveRed2Right(Node<typeT>* node);

            /**
             * @brief Find the leftmost node (smallest key)
             * @param node The node where the search will begin
             * @return Pointer to the leftmost node
             */
            Node<typeT>* FindLeftMostNode(Node<typeT>* node);

            /**
             * @brief Delete the leftmost node
             * @param node The node where the search for the leftmost node will begin
             * @return
             */
            Node<typeT>* DeleteLeftMostNode(Node<typeT>* node);

            /**
             * @brief Modify the color of a family of nodes (node and its children)
             * @param parent The node where the modification will occur
             */
            void ChangeFamilyColor(Node<typeT>* parent);

            /**
             * @brief Delete the entire Red-Black Tree (recursive call)
             */
            void Clear(Node<typeT>*& node);

            /**
             * @brief Print the tree
             * @param output The file where the printing will be done
             * @param node The current node
             * @param sideIsLeft Should receive True if the node is on the left side or
             * False if the node is on the right side
             */
            void DumpTree(Node<typeT>*&      node,
                          const std::string& vBar,
                          std::ofstream&     output,
                          bool               sideIsLeft);

            /**
             * @brief Check the number of black nodes in the tree
             * @param node The current node in the recursive call
             * @return The number of black nodes
             */
            std::size_t GetBlackNodeCount(Node<typeT>*& node);

            /**
             * @brief Check if the Red-Black Tree properties are satisfied
             * @param node The current node in the recursive call
             */
            bool IsRedBlackTreeBalanced(Node<typeT>*& node);

        public:
            RedBlackTree(const lessComparator&  lessComp  = lessComparator(),
                         const equalComparator& equalComp = equalComparator());

            ~RedBlackTree();

            /**
             * @brief Overload to insert a new element without the node pointer
             * @param key Key to be stored in the Red-Black Tree
             * @return Pointer to the inserted node
             */
            Node<typeT>* Insert(const typeT& key);

            /**
             * @brief Search for the node containing a specific key
             * @param key The key used in the search
             * @return Pointer to the node or nullptr if the node was not found
             */
            Node<typeT>* Search(const typeT& key);

            /**
             * @brief Returns the number of elements in the Red-Black Tree
             * @return Number of elements in the Red-Black Tree
             */
            std::size_t Size();

            /**
             * @brief Checks if the Red-Black Tree is empty
             * @return True if it's empty, False otherwise
             */
            bool IsEmpty();

            /**
             * @brief Checks if the tree is balanced
             * @return True if it's balanced, False otherwise
             */
            bool IsRedBlackTreeBalanced();

            /**
             * @brief Prints the tree
             * @param output The file where the printing will be done
             */
            void DumpTree(std::ofstream& output);

            /**
             * @brief Remove an element from the Red-Black Tree
             * @param key Key of the element to be removed
             */
            void Remove(const typeT& key);

            /**
             * @brief Deletes the entire Red-Black Tree
             */
            void Clear();
    };

    template<typename typeT, typename lessComparator, typename equalComparator>
    RedBlackTree<typeT, lessComparator, equalComparator>::RedBlackTree(
        const lessComparator&  lessComp,
        const equalComparator& equalComp)
        : m_lessComp(lessComp),
          m_equalComp(equalComp)
    {
        this->m_root     = nullptr;
        this->m_numNodes = 0;
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    RedBlackTree<typeT, lessComparator, equalComparator>::~RedBlackTree()
    {
        this->Clear();
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>*
    RedBlackTree<typeT, lessComparator, equalComparator>::Insert(const typeT& key)
    {
        if (this->m_root == nullptr)
        {
            this->m_root = new Node<typeT>(key);
            this->m_numNodes++;
            this->m_root->SetColor(BLACK);
            return this->m_root;
        }
        else
        {
            if (this->m_lessComp(key, this->m_root->GetValue()))
                return this->Insert(this->m_root, this->m_root->GetLeftNode(), key);

            else
                return this->Insert(this->m_root, this->m_root->GetRightNode(), key);
        }
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>*
    RedBlackTree<typeT, lessComparator, equalComparator>::Insert(Node<typeT>*  parent,
                                                                 Node<typeT>*& node,
                                                                 const typeT&  key)
    {
        if (node == nullptr)
        {
            node = new Node<typeT>(key, parent);
            this->m_numNodes++;
            this->FixInsert(node);
            return node;
        }
        else
        {
            if (this->m_lessComp(key, node->GetValue()))
                return this->Insert(node, node->GetLeftNode(), key);

            else
                return this->Insert(node, node->GetRightNode(), key);
        }
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void
    RedBlackTree<typeT, lessComparator, equalComparator>::FixInsert(Node<typeT>* node)
    {
        Node<typeT>* uncle = nullptr;

        while (node != this->m_root and node->GetParent() and
               node->GetParent()->GetColor() == RED)
        {
            if (node->GetParent() == node->GetParent()->GetParent()->GetRightNode())
            {

                uncle = node->GetParent()->GetParent()->GetLeftNode();

                if (uncle and uncle->GetColor() == RED)
                {
                    uncle->SetColor(BLACK);
                    node->GetParent()->SetColor(BLACK);
                    node->GetParent()->GetParent()->SetColor(RED);
                    node = node->GetParent()->GetParent();
                }
                else
                {
                    if (node == node->GetParent()->GetLeftNode())
                    {
                        node = node->GetParent();
                        this->RotateRight(node);
                    }
                    node->GetParent()->SetColor(BLACK);
                    node->GetParent()->GetParent()->SetColor(RED);
                    this->RotateLeft(node->GetParent()->GetParent());
                }
            }
            else
            {
                uncle = node->GetParent()->GetParent()->GetRightNode();

                if (uncle and uncle->GetColor() == RED)
                {
                    uncle->SetColor(BLACK);
                    node->GetParent()->SetColor(BLACK);
                    node->GetParent()->GetParent()->SetColor(RED);
                    node = node->GetParent()->GetParent();
                }
                else
                {
                    if (node == node->GetParent()->GetRightNode())
                    {
                        node = node->GetParent();
                        this->RotateLeft(node);
                    }
                    node->GetParent()->SetColor(BLACK);
                    node->GetParent()->GetParent()->SetColor(RED);
                    this->RotateRight(node->GetParent()->GetParent());
                }
            }
        }
        this->m_root->SetColor(BLACK);
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    std::size_t RedBlackTree<typeT, lessComparator, equalComparator>::Size()
    {
        return this->m_numNodes;
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    bool RedBlackTree<typeT, lessComparator, equalComparator>::IsEmpty()
    {
        return (this->m_numNodes == 0);
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void RedBlackTree<typeT, lessComparator, equalComparator>::Remove(const typeT& key)
    {
        this->DeleteNode(this->Search(key));
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void
    RedBlackTree<typeT, lessComparator, equalComparator>::DeleteNode(Node<typeT>* node)
    {
        if (node == nullptr)
            return;

        Node<typeT>* nodeCopy = node;
        Node<typeT>* aux;
        Color        nodeColor = node->GetColor();

        if (node->GetLeftNode() == nullptr)
        {
            aux = node->GetRightNode();

            this->Transplant(node, node->GetRightNode());
        }
        else if (node->GetRightNode() == nullptr)
        {
            aux = node->GetLeftNode();

            this->Transplant(node, node->GetLeftNode());
        }
        else
        {
            nodeCopy  = this->FindLeftMostNode(node->GetRightNode());
            nodeColor = nodeCopy->GetColor();
            aux       = nodeCopy->GetRightNode();

            if (aux and nodeCopy->GetParent() == node)
            {
                aux->SetParent(nodeCopy);
            }
            else
            {
                this->Transplant(nodeCopy, node->GetRightNode());
                nodeCopy->SetRightNode(node->GetRightNode());

                if (nodeCopy->GetRightNode() and nodeCopy->GetRightNode()->GetParent())
                    nodeCopy->GetRightNode()->SetParent(nodeCopy);
            }

            this->Transplant(node, nodeCopy);

            nodeCopy->SetLeftNode(node->GetLeftNode());
            nodeCopy->GetLeftNode()->SetParent(nodeCopy);
            nodeCopy->SetColor(node->GetColor());
        }

        delete node;
        this->m_numNodes--;

        if (nodeColor == BLACK)
        {
            this->FixDelete(aux);
        }
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void
    RedBlackTree<typeT, lessComparator, equalComparator>::FixDelete(Node<typeT>* node)
    {
        Node<typeT>* aux = nullptr;

        while (node != this->m_root and node and node->GetColor() == BLACK)
        {
            if (node == node->GetParent()->GetLeftNode())
            {
                aux = node->GetParent()->GetRightNode();

                if (aux and aux->GetColor() == RED)
                {
                    aux->SetColor(BLACK);
                    node->GetParent()->SetColor(RED);
                    this->RotateLeft(node->GetParent());
                    aux = node->GetParent()->GetRightNode();
                }

                if (aux->GetLeftNode() and aux->GetLeftNode()->GetColor() == BLACK and
                    aux->GetRightNode() and aux->GetRightNode()->GetColor() == BLACK)
                {
                    aux->SetColor(RED);
                    node = node->GetParent();
                }
                else
                {
                    if (aux->GetRightNode() and
                        aux->GetRightNode()->GetColor() == BLACK)
                    {
                        aux->GetLeftNode()->SetColor(BLACK);
                        aux->SetColor(RED);
                        this->RotateRight(aux);
                        aux = node->GetParent()->GetRightNode();
                    }

                    aux->SetColor(node->GetParent()->GetColor());
                    node->GetParent()->SetColor(BLACK);
                    aux->GetRightNode()->SetColor(BLACK);
                    this->RotateLeft(node->GetParent());
                    node = this->m_root;
                }
            }
            else
            {
                aux = node->GetParent()->GetLeftNode();
                if (aux and aux->GetColor() == RED)
                {
                    aux->SetColor(BLACK);
                    node->GetParent()->SetColor(RED);
                    this->RotateRight(node->GetParent());
                    aux = node->GetParent()->GetLeftNode();
                }

                // Possível erro nesse if
                if (aux->GetRightNode() and aux->GetRightNode()->GetColor() == BLACK)
                {
                    aux->SetColor(RED);
                    node = node->GetParent();
                }
                else
                {
                    if (aux->GetLeftNode() and aux->GetLeftNode()->GetColor() == BLACK)
                    {
                        aux->GetRightNode()->SetColor(BLACK);
                        aux->SetColor(RED);
                        this->RotateLeft(aux);
                        aux = node->GetParent()->GetLeftNode();
                    }
                }

                aux->SetColor(node->GetParent()->GetColor());
                node->GetParent()->SetColor(BLACK);
                aux->GetLeftNode()->SetColor(BLACK);
                this->RotateRight(node->GetParent());
                node = this->m_root;
            }
        }
        if (node != nullptr)
            node->SetColor(BLACK);
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void RedBlackTree<typeT, lessComparator, equalComparator>::Transplant(
        Node<typeT>*& node1,
        Node<typeT>*& node2)
    {
        if (node1->GetParent() == nullptr)
            this->m_root = node2;

        else if (node1 == node1->GetParent()->GetLeftNode())
            node1->GetParent()->SetLeftNode(node2);

        else
            node1->GetParent()->SetRightNode(node2);

        if (node2 != nullptr)
            node2->SetParent(node1->GetParent());
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>*
    RedBlackTree<typeT, lessComparator, equalComparator>::Search(const typeT& key)
    {
        return this->Search(this->m_root, key);
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>*
    RedBlackTree<typeT, lessComparator, equalComparator>::Search(Node<typeT>* node,
                                                                 const typeT& key)
    {
        if (node == nullptr or this->m_equalComp(key, node->GetValue()))
            return node;

        if (this->m_lessComp(key, node->GetValue()))
            return this->Search(node->GetLeftNode(), key);

        else
            return this->Search(node->GetRightNode(), key);
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>*
    RedBlackTree<typeT, lessComparator, equalComparator>::RotateLeft(Node<typeT>* node)
    {
        if (node == nullptr or node->GetRightNode() == nullptr)
            return node;

        Node<typeT>* pivot = node->GetRightNode();
        node->SetRightNode(pivot->GetLeftNode());

        if (pivot->GetLeftNode() != nullptr)
            pivot->GetLeftNode()->SetParent(node);

        pivot->SetParent(node->GetParent());

        if (node->GetParent() == nullptr)
            this->m_root = pivot;

        else if (node == node->GetParent()->GetLeftNode())
            node->GetParent()->SetLeftNode(pivot);

        else
            node->GetParent()->SetRightNode(pivot);

        pivot->SetLeftNode(node);
        node->SetParent(pivot);

        return pivot;
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>*
    RedBlackTree<typeT, lessComparator, equalComparator>::RotateRight(Node<typeT>* node)
    {
        if (node == nullptr or node->GetLeftNode() == nullptr)
            return node;

        Node<typeT>* pivot = node->GetLeftNode();
        node->SetLeftNode(pivot->GetRightNode());

        if (pivot->GetRightNode() != nullptr)
            pivot->GetRightNode()->SetParent(node);

        pivot->SetParent(node->GetParent());

        if (node->GetParent() == nullptr)
            this->m_root = pivot;

        else if (node == node->GetParent()->GetLeftNode())
            node->GetParent()->SetLeftNode(pivot);

        else
            node->GetParent()->SetRightNode(pivot);

        pivot->SetRightNode(node);
        node->SetParent(pivot);

        return pivot;
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>* RedBlackTree<typeT, lessComparator, equalComparator>::MoveRed2Left(
        Node<typeT>* node)
    {
        this->ChangeFamilyColor(node);

        if (node->GetRightNode() != nullptr and
            node->GetRightNode()->GetLeftNode() != nullptr and
            node->GetRightNode()->GetLeftNode()->GetColor() == RED)
        {
            node->SetRightNode(this->RotateRight(node->GetRightNode()));
            node = this->RotateLeft(node);
            this->ChangeFamilyColor(node);
        }

        return node;
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>* RedBlackTree<typeT, lessComparator, equalComparator>::MoveRed2Right(
        Node<typeT>* node)
    {
        this->ChangeFamilyColor(node);

        if (node->GetLeftNode() != nullptr and
            node->GetLeftNode()->GetLeftNode() != nullptr and
            node->GetLeftNode()->GetLeftNode()->GetColor() == RED)
        {
            node = this->RotateRight(node);
            this->ChangeFamilyColor(node);
        }

        return node;
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void RedBlackTree<typeT, lessComparator, equalComparator>::ChangeFamilyColor(
        Node<typeT>* parent)
    {
        parent->SetColor(parent->GetColor() == BLACK ? RED : BLACK);

        if (parent->GetLeftNode() != nullptr)
            parent->GetLeftNode()->SetColor(
                parent->GetLeftNode()->GetColor() == BLACK ? RED : BLACK);

        if (parent->GetRightNode() != nullptr)
            parent->GetRightNode()->SetColor(
                parent->GetRightNode()->GetColor() == BLACK ? RED : BLACK);
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>* RedBlackTree<typeT, lessComparator, equalComparator>::FindLeftMostNode(
        Node<typeT>* node)
    {
        Node<typeT>* current = node;

        while (current and current->GetLeftNode() != nullptr)
            current = current->GetLeftNode();

        return current;
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    Node<typeT>*
    RedBlackTree<typeT, lessComparator, equalComparator>::DeleteLeftMostNode(
        Node<typeT>* node)
    {
        if (node == nullptr)
            return nullptr;

        if (node->GetLeftNode() == nullptr)
        {
            Node<typeT>* rightChild = node->GetRightNode();
            delete node;
            this->m_numNodes--;
            return rightChild;
        }

        if (node->GetLeftNode() and node->GetLeftNode()->GetColor() == BLACK and
            node->GetLeftNode()->GetLeftNode() and
            node->GetLeftNode()->GetLeftNode()->GetColor() == BLACK)
        {
            node = this->MoveRed2Left(node);
        }

        node->SetLeftNode(DeleteLeftMostNode(node->GetLeftNode()));
        this->FixDelete(node);
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void RedBlackTree<typeT, lessComparator, equalComparator>::Clear()
    {
        this->Clear(this->m_root);
        this->m_root = nullptr;
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void RedBlackTree<typeT, lessComparator, equalComparator>::Clear(Node<typeT>*& node)
    {
        if (node != nullptr)
        {

            this->Clear(node->GetLeftNode());

            this->Clear(node->GetRightNode());

            delete node;
            this->m_numNodes--;
        }
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void RedBlackTree<typeT, lessComparator, equalComparator>::DumpTree(
        std::ofstream& output)
    {
        if (this->m_root != nullptr)
        {
            output << this->m_root->GetValue() << ":" << this->m_root->m_color
                   << std::endl;
            this->DumpTree(this->m_root->GetLeftNode(), "", output, true);
            this->DumpTree(this->m_root->GetRightNode(), "", output, false);
        }
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    void RedBlackTree<typeT, lessComparator, equalComparator>::DumpTree(
        Node<typeT>*&      node,
        const std::string& vBar,
        std::ofstream&     output,
        bool               sideIsLeft)
    {
        if (node != nullptr)
        {
            if (sideIsLeft)
            {
                output << vBar << "├───" << node->GetValue() << ":" << node->GetColor()
                       << std::endl;
            }
            else
            {
                output << vBar << "└───" << node->GetValue() << ":" << node->GetColor()
                       << std::endl;
            }

            this->DumpTree(node->GetLeftNode(),
                           vBar + (sideIsLeft ? "│    " : "     "),
                           output,
                           true);

            this->DumpTree(node->GetRightNode(),
                           vBar + (sideIsLeft ? "│    " : "     "),
                           output,
                           false);
        }
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    bool RedBlackTree<typeT, lessComparator, equalComparator>::IsRedBlackTreeBalanced(
        Node<typeT>*& node)
    {
        if (node == nullptr)
            return true;

        // Verifica a propriedade das cores
        if (node->GetColor() != RED and node->GetColor() != BLACK)
            return false;

        // Verifica a propriedade da raiz
        if (node == m_root and node->GetColor() != BLACK)
            return false;

        // Verifica a propriedade dos filhos vermelhos
        if (node->GetColor() == RED)
        {
            if (node->GetLeftNode() and node->GetLeftNode()->GetColor() != BLACK)
                return false;

            if (node->GetRightNode() and node->GetRightNode()->GetColor() != BLACK)
                return false;
        }

        // Verifica a propriedade dos caminhos pretos

        std::size_t leftBlackCount  = GetBlackNodeCount(node->GetLeftNode());
        std::size_t rightBlackCount = GetBlackNodeCount(node->GetRightNode());

        if (leftBlackCount != rightBlackCount)
            return false;

        return IsRedBlackTreeBalanced(node->GetLeftNode()) and
               IsRedBlackTreeBalanced(node->GetRightNode());
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    std::size_t RedBlackTree<typeT, lessComparator, equalComparator>::GetBlackNodeCount(
        Node<typeT>*& node)
    {
        if (node == nullptr)
            return 1; // Folhas nulas são consideradas pretas

        std::size_t leftCount  = GetBlackNodeCount(node->GetLeftNode());
        std::size_t rightCount = GetBlackNodeCount(node->GetRightNode());

        // Incrementa o contador apenas para nós pretos
        return node->GetColor() == BLACK ? leftCount + 1 : rightCount;
    }

    template<typename typeT, typename lessComparator, typename equalComparator>
    bool RedBlackTree<typeT, lessComparator, equalComparator>::IsRedBlackTreeBalanced()
    {
        return this->IsRedBlackTreeBalanced(this->m_root);
    }
} // namespace rbtree
#endif // RED_BLACK_TREE_H_
