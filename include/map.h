/*
 * Filename: map.h
 * Created on: June 28, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef MAP_H_
#define MAP_H_

#include "comparators.h"
#include "node_rbtree.h"
#include "pair.h"
#include "red_black_tree.h"

namespace rbtree
{
    /**
     * @brief A Red-Black Tree-based Map implementation
     *
     * This class represents a map implemented using a Red-Black Tree data structure.
     * It stores key-value pairs where 'typeK' represents the type of the keys, and
     * 'typeV' represents the type of the values stored in the map
     *
     * The Red-Black Tree structure is used to maintain the map's properties and provide
     * efficient operations like insertion, deletion, and retrieval
     *
     * Time Complexity:
     *   Function       Worst case      Amortized
     *    insert         O(log n)         O(1)
     *    delete         O(log n)         O(1)
     *    search         O(log n)       O(log n)
     *
     * Space Complexity: O(n)
     *
     * @tparam typeK The type of the keys in the map
     * @tparam typeV The type of the values associated with the keys
     */
    template<typename typeK, typename typeV>
    class Map : private RedBlackTree<Pair<typeK, typeV>,
                                     decltype(comparators::PairLess<typeK, typeV>),
                                     decltype(comparators::PairEqual<typeK, typeV>)>
    {
        private:
            using RBTree = RedBlackTree<Pair<typeK, typeV>,
                                        decltype(comparators::PairLess<typeK, typeV>),
                                        decltype(comparators::PairEqual<typeK, typeV>)>;

            using NodeType = Node<Pair<typeK, typeV>>;

        public:
            Map();

            ~Map();

            /**
             * @brief Overload of the operator []
             * @param key Key to be looked up
             * @return The value corresponding to the key
             *
             * If the key is not in the map, it will be inserted with a default value
             **/
            typeV& operator[](const typeK& key);

            /**
             * @brief Access an element in the map
             * @param key Key to be looked up
             * @return The value corresponding to the key
             *
             * If the key is not in the map, it will be inserted with a default value
             **/
            typeV& At(const typeK& key);

            /**
             * @brief Get the value associated with a key
             * @param key Key to be looked up
             * @return The value corresponding to the key
             *
             * If the key is not in the map,
             **/
            typeV& Get(const typeK& key);

            /**
             * @brief Overload to insert a new element without a node pointer
             * @param key, value Key and value to be inserted
             * @return Pointer to the inserted node
             */
            NodeType* Insert(const typeK& key, const typeV& value);

            /**
             * @return Number of elements in the map
             */
            std::size_t Size() const;

            /**
             * @return True if it's empty, False otherwise
             */
            bool IsEmpty();

            /**
             * @brief Checks if a key is in the map
             * @return True if it is, False otherwise
             **/
            bool Contains(const typeK& key);

            /**
             * @brief Removes an element from the map
             * @param key Key of the element to be removed
             **/
            void Remove(const typeK& key);

            /**
             * @brief Deletes the entire Map
             */
            void Clear();

            // iterator
            using pointer   = NodeType*;
            using reference = NodeType&;

            typedef struct Iterator
            {
                private:
                    pointer m_ptr;

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
                        if (m_ptr == nullptr)
                            return *this;

                        if (m_ptr->GetRightNode() != nullptr)
                        {
                            m_ptr = m_ptr->GetRightNode();

                            while (m_ptr->GetLeftNode() != nullptr)
                                m_ptr = m_ptr->GetLeftNode();
                        }
                        else
                        {
                            while (true)
                            {
                                if (m_ptr->GetParent() == nullptr)
                                {
                                    m_ptr = nullptr;
                                    break;
                                }

                                if (m_ptr == m_ptr->GetParent()->GetLeftNode())
                                {
                                    m_ptr = m_ptr->GetParent();
                                    break;
                                }

                                m_ptr = m_ptr->GetParent();
                            }
                        }

                        return *this;
                    }

                    Iterator operator++(int)
                    {
                        Iterator tmp = *this;
                        ++(*this);
                        return tmp;
                    }

                    bool operator==(const Iterator& other) const
                    {
                        return m_ptr == other.m_ptr;
                    }

                    bool operator!=(const Iterator& other) const
                    {
                        return not(*this == other);
                    }

                    Pair<typeK, typeV>& operator*()
                    {
                        return m_ptr->GetValue();
                    }

            } Iterator;

            Iterator begin()
            {
                NodeType* leftMost = RBTree::m_root;

                while (leftMost != nullptr and leftMost->GetLeftNode() != nullptr)
                    leftMost = leftMost->GetLeftNode();

                return Iterator(leftMost);
            }

            Iterator end()
            {
                return Iterator(nullptr);
            }
    };

    template<typename typeK, typename typeV>
    Map<typeK, typeV>::Map()
        : RedBlackTree<Pair<typeK, typeV>,
                       decltype(comparators::PairLess<typeK, typeV>),
                       decltype(comparators::PairEqual<typeK, typeV>)>()
    { }

    template<typename typeK, typename typeV>
    Map<typeK, typeV>::~Map()
    { }

    template<typename typeK, typename typeV>
    typeV& Map<typeK, typeV>::operator[](const typeK& key)
    {
        return RBTree::Insert(Pair<typeK, typeV>(key, typeV()))->GetValue().GetSecond();
    }

    template<typename typeK, typename typeV>
    typeV& Map<typeK, typeV>::At(const typeK& key)
    {
        return RBTree::Insert(Pair<typeK, typeV>(key, typeV()))->GetValue().GetSecond();
    }

    template<typename typeK, typename typeV>
    typeV& Map<typeK, typeV>::Get(const typeK& key)
    {
        NodeType* node = RBTree::Search(Pair<typeK, typeV>(key, typeV()));

        if (node == nullptr)
            throw std::out_of_range("Key not found in the map");

        return node->GetValue().GetSecond();
    }

    template<typename typeK, typename typeV>
    Node<Pair<typeK, typeV>>* Map<typeK, typeV>::Insert(const typeK& key,
                                                        const typeV& value)
    {
        return RBTree::Insert(Pair<typeK, typeV>(key, value));
    }

    template<typename typeK, typename typeV>
    std::size_t Map<typeK, typeV>::Size() const
    {
        return RBTree::Size();
    }

    template<typename typeK, typename typeV>
    bool Map<typeK, typeV>::IsEmpty()
    {
        return RBTree::IsEmpty();
    }

    template<typename typeK, typename typeV>
    bool Map<typeK, typeV>::Contains(const typeK& key)
    {
        return (RBTree::Search(Pair<typeK, typeV>(key, typeV())) != nullptr);
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::Remove(const typeK& key)
    {
        RBTree::Remove(Pair<typeK, typeV>(key, typeV()));
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::Clear()
    {
        RBTree::Clear();
    }
} // namespace rbtree

#endif // MAP_H_
