/*
 * Filename: node.h
 * Created on: May 12, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 *
 * This file contains the implementation of the base 'Node' classes.
 *
 * `slkd::Node` is the base node that contains only a pointer to the next element,
 * particularly useful for implementing singly linked lists.
 *
 * `dlkd::Node` is the base node that contains pointers to both left and right nodes,
 * useful for implementing binary trees and doubly linked lists.
 */

#ifndef NODE_H_
#define NODE_H_

// Singly linked namespace
namespace slkd
{
    template<typename typeT>
    class Node
    {
        private:
            Node<typeT>* m_next;

        protected:
            typeT m_value;

        public:
            Node(typeT k)
                : m_next(nullptr),
                  m_value(k)
            { }

            Node(typeT k, Node* next)
                : m_next(next),
                  m_value(k)
            { }

            virtual ~Node() = default;

            /**
             * @brief Sets the value of the node
             * @param newKey The new value to be assigned to the node
             */
            void SetValue(typeT newValue)
            {
                this->m_value = newValue;
            }

            /**
             * @brief Gets the value of the node
             * @return The value of the node
             */
            typeT& GetValue()
            {
                return this->m_value;
            }

            /**
             * @brief Sets the next child node of the current node
             * @param nnode Pointer to the next child node to be set
             */
            void SetNextNode(Node<typeT>* nnode)
            {
                this->m_next = nnode;
            }

            /**
             * @brief Gets the next child node of the current node
             * @return Pointer to the next child node
             */
            Node<typeT>* GetNextNode()
            {
                return this->m_next;
            }
    };
} // namespace slkd

// Doubly linked namespace
namespace dlkd
{
    template<typename typeT>
    class Node
    {
        private:
            Node<typeT>* m_left;
            Node<typeT>* m_right;

        protected:
            typeT m_value;

        public:
            Node(typeT k)
                : m_left(nullptr),
                  m_right(nullptr),
                  m_value(k)
            { }

            Node(Node* left, typeT k)
                : m_left(left),
                  m_right(nullptr),
                  m_value(k)
            { }

            Node(typeT k, Node* right)
                : m_left(nullptr),
                  m_right(right),
                  m_value(k)
            { }

            Node(typeT k, Node* left, Node* right)
                : m_left(left),
                  m_right(right),
                  m_value(k)
            { }

            virtual ~Node() = default;

            /**
             * @brief Sets the value of the node
             * @param newKey The new value to be assigned to the node
             */
            void SetValue(typeT newValue)
            {
                this->m_value = newValue;
            }

            /**
             * @brief Sets the left child node of the current node
             * @param lnode Pointer to the left child node to be set
             */
            void SetLeftNode(Node<typeT>* lnode)
            {
                this->m_left = lnode;
            }

            /**
             * @brief Sets the right child node of the current node
             * @param rnode Pointer to the right child node to be set
             */
            void SetRightNode(Node<typeT>* rnode)
            {
                this->m_right = rnode;
            }

            /**
             * @brief Gets the value of the node
             * @return The key value of the node
             */
            typeT& GetValue()
            {
                return this->m_value;
            }

            /**
             * @brief Gets the left child node of the current node
             * @return Pointer to the left child node
             */
            Node<typeT>*& GetLeftNode()
            {
                return this->m_left;
            }

            /**
             * @brief Gets the right child node of the current node
             * @return Pointer to the right child node
             */
            Node<typeT>*& GetRightNode()
            {
                return this->m_right;
            };
    };
} // namespace dlkd

#endif // NODE_H_
