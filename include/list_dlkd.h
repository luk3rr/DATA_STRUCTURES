/*
 * Filename: list_dlkd.h
 * Created on: May 13, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef LIST_DLKD_H_
#define LIST_DLKD_H_

#include <cstddef>
#include <iostream>

#include "list_excpt.h"
#include "node.h"

// Doubly linked namespace
namespace dlkd
{
    /**
     * @brief Doubly linked list data structure
     *
     * This class represents a doubly linked list, where 'typeT' is the type of the
     * elements stored in the list
     *
     * @tparam typeT The type of elements in the list
     *
     * TODO: Implement insert(value, pos)
     */
    template<typename typeT>
    class List
    {
        private:
            Node<typeT>* m_head;
            Node<typeT>* m_tail;
            std::size_t  m_size;

            /**
             * @brief Remove a node from the list.
             * @param node Pointer to the node.
             */
            void Remove(Node<typeT>* node);

            /**
             * @brief Search for the node containing the key.
             * @param key The key to be searched.
             * @param node Next search node.
             * @return Pointer to the node containing the key.
             */
            Node<typeT>* Search(Node<typeT>* node, typeT& key);

        public:
            /**
             * @brief Default constructor
             */
            List();

            /**
             * @brief Copy constructor
             **/
            List(const List<typeT>& other);

            ~List();

            /**
             * @brief Assignment operator
             **/
            List<typeT>& operator=(const List<typeT>& other);

            /**
             * @brief Overloaded output stream operator to print the Pair
             * @param os The output stream
             * @return The modified output stream
             */
            std::ostream& operator<<(std::ostream& os);

            /**
             * @brief Get the number of keys stored in the list
             * @return The number of keys
             */
            std::size_t Size();

            /**
             * @brief Check if the list is empty
             * @return True if the list is empty, False otherwise
             */
            bool IsEmpty();

            /**
             * @brief Insert a new key into the list
             * @param key The value to be stored
             */
            void PushBack(typeT key);

            /**
             * @brief Remove a key from the list
             * @param key The value to be removed
             */
            void Remove(typeT key);

            /**
             * @brief Clear the entire list
             */
            void Clear();

            /**
             * @brief Search for the node containing the key
             * @param key The key to be searched
             * @return Pointer to the node containing the key
             */
            Node<typeT>* Search(typeT& key);

            /**
             * @brief Return the first element of the list
             * @return The key of the first element of the list
             */
            typeT Front();

            /**
             * @brief Return the last element of the list
             * @return The key of the last element of the list
             */
            typeT Back();

            using pointer   = dlkd::Node<typeT>*;
            using reference = dlkd::Node<typeT>&;

            typedef struct Iterator
            {
                public:
                    Iterator(pointer ptr)
                        : m_ptr(ptr)
                    { }

                    Iterator() { }

                    reference operator*() const
                    {
                        return *m_ptr;
                    }

                    pointer operator->()
                    {
                        return m_ptr;
                    }

                    Iterator& operator++()
                    {
                        m_ptr = m_ptr->GetRightNode();
                        return *this;
                    }

                    Iterator operator++(int)
                    {
                        Iterator tmp = *this;
                        ++(*this);
                        return tmp;
                    }

                    friend bool operator==(const Iterator& a, const Iterator& b)
                    {
                        return a.m_ptr == b.m_ptr;
                    };

                    friend bool operator!=(const Iterator& a, const Iterator& b)
                    {
                        return a.m_ptr != b.m_ptr;
                    };

                private:
                    pointer m_ptr;

            } Iterator;

            Iterator begin()
            {
                return Iterator(this->m_head);
            }

            Iterator end()
            {
                return Iterator(this->m_tail);
            }
    };

    template<typename typeT>
    List<typeT>::List()
    {
        this->m_head = nullptr;
        this->m_tail = nullptr;
        this->m_size = 0;
    }

    template<typename typeT>
    List<typeT>::List(const List<typeT>& other)
    {
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;

        Node<typeT>* current = other.m_head;
        while (current != nullptr)
        {
            PushBack(current->GetValue());
            current = current->GetRight();
        }
    }

    template<typename typeT>
    List<typeT>::~List()
    {
        this->Clear();
    }

    template<typename typeT>
    std::ostream& List<typeT>::operator<<(std::ostream& os)
    {
        Node<typeT>* current = this->m_head;

        while (current != nullptr)
        {
            os << current->GetValue() << " ";
            current = current->GetRight();
        }

        return os;
    }

    template<typename typeT>
    std::size_t List<typeT>::Size()
    {
        return this->m_size;
    }

    template<typename typeT>
    bool List<typeT>::IsEmpty()
    {
        return (this->m_size == 0);
    }

    template<typename typeT>
    void List<typeT>::PushBack(typeT key)
    {
        if (this->m_head == nullptr)
        {
            this->m_head = this->m_tail = new Node<typeT>(key);
        }
        else
        {
            this->m_tail->SetRightNode(new Node<typeT>(this->m_tail, key));
            this->m_tail = this->m_tail->GetRightNode();
        }
        this->m_size++;
    }

    template<typename typeT>
    Node<typeT>* List<typeT>::Search(typeT& key)
    {
        if (this->m_size == 0)
            return nullptr;

        if (this->m_head->GetValue() == key)
            return this->m_head;

        else
            return this->Search(this->m_head->GetRightNode(), key);
    }

    template<typename typeT>
    Node<typeT>* List<typeT>::Search(Node<typeT>* node, typeT& key)
    {
        if (node == nullptr)
            return nullptr;

        if (node->GetValue() == key)
            return node;

        else
            return this->Search(node->GetRightNode(), key);
    }

    template<typename typeT>
    void List<typeT>::Remove(typeT key)
    {
        Node<typeT>* node = this->Search(key);
        this->Remove(node);
    }

    template<typename typeT>
    void List<typeT>::Remove(Node<typeT>* node)
    {
        if (node == nullptr)
            return;

        if (node == this->m_head and node == this->m_tail)
        {
            this->m_head = nullptr;
            this->m_tail = nullptr;
        }
        else if (node == this->m_head)
        {
            this->m_head = node->GetRightNode();
            this->m_head->SetLeftNode(nullptr);
        }
        else if (node == this->m_tail)
        {
            this->m_tail = this->m_tail->GetLeftNode();
            this->m_tail->SetRightNode(nullptr);
        }
        else
        {
            node->GetLeftNode()->SetRightNode(node->GetRightNode());
            node->GetRightNode()->SetLeftNode(node->GetLeftNode());
        }

        delete node;
        this->m_size--;
    }

    template<typename typeT>
    void List<typeT>::Clear()
    {
        while (not this->IsEmpty())
        {
            this->Remove(this->m_head);
        }
    }

    template<typename typeT>
    typeT List<typeT>::Front()
    {
        if (this->IsEmpty())
            throw lstexcpt::ListIsEmpty();

        return this->m_head->GetValue();
    }

    template<typename typeT>
    typeT List<typeT>::Back()
    {
        if (this->IsEmpty())
            throw lstexcpt::ListIsEmpty();

        return this->m_tail->GetValue();
    }
} // namespace dlkd

#endif // LIST_DLKD_H_
