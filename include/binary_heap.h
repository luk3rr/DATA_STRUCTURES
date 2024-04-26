/*
 * Filename: binary_heap.h
 * Created on: November  3, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include <cstddef>

#include "comparators.h"
#include "heap_base.h"
#include "vector.h"

namespace bheap
{
    /**
     * @brief Implementation of a binary heap data structure
     *
     * This class implements a binary heap data structure, which can be used as a
     * base for various heap-based algorithms and data structures, such as priority
     * queues, heap sort etc
     *
     * A binary heap maintains the heap property (minimum or maximum) and provides
     * efficient operations for insertion and removal of elements.
     *
     * Worst-case time complexities:
     *   - Push: O(1 + log n) where log n is the execution time of HeapifyDown
     *   - Pop: O(1 + log n) where log n is the execution time of HeapifyUp
     *   - Peek: O(1)
     *
     * @tparam typeT The type of elements stored in the binary heap
     * @tparam Compare The custom comparator used to maintain the heap property
     *
     * NOTE: By default, the 'Compare' parameter is set to 'comparators::less<typeT>' for a
     * minimum priority
     */
    template<typename typeT, typename Compare = decltype(comparators::Less<typeT>)>
    class BinaryHeap : HeapBase<typeT>
    {
        private:
            Vector<typeT> m_heap;
            Compare       m_comp; // Custom comparator

        protected:
            /**
             * @brief Adjusts the heap after the removal of an element
             * @param index Index of the removed element
             **/
            void HeapifyDown(std::size_t index) override;

            /**
             * @brief Adjusts the heap after the insertion of an element
             * @param index Index of the inserted element
             **/
            void HeapifyUp(std::size_t index) override;

        public:
            /**
             * @brief Constructor for BinaryHeap
             * @param comp The custom comparator to use (default is the standard
             * comparator)
             */
            BinaryHeap(const Compare& comp = Compare());
            ~BinaryHeap();

            /**
             * @brief Insert a new element into the heap
             * @param element New element
             **/
            void Push(typeT element) override;

            /**
             * @brief Get the element with the priority value considered the lowest or
             * highest without removing it
             * @return The element with the lowest or highest priority value
             **/
            typeT Peek() override;

            /**
             * @brief Remove and return the element with the priority value considered
             * the lowest or highest
             * @return The element with the lowest or highest priority value
             **/
            typeT Pop() override;

            /**
             * @brief Check if the heap is empty
             * @return True if it is empty, False otherwis
             **/
            bool IsEmpty() override;

            /**
             * @brief Get the current size of the heap
             * @return The current size of the heap
             **/
            std::size_t Size() override;

            /**
             * @brief Delete all nodes in the heap
             **/
            void Clear() override;
    };

    template<typename typeT, typename Compare>
    BinaryHeap<typeT, Compare>::BinaryHeap(const Compare& comp)
        : m_comp(comp)
    { }

    template<typename typeT, typename Compare>
    BinaryHeap<typeT, Compare>::~BinaryHeap()
    { }

    template<typename typeT, typename Compare>
    void BinaryHeap<typeT, Compare>::Push(typeT element)
    {
        this->m_heap.PushBack(element);
        this->HeapifyUp(this->m_heap.Size() - 1);
    }

    template<typename typeT, typename Compare>
    typeT BinaryHeap<typeT, Compare>::Peek()
    {
        return this->m_heap[0];
    }

    template<typename typeT, typename Compare>
    typeT BinaryHeap<typeT, Compare>::Pop()
    {
        typeT toPop = this->m_heap[0];
        this->m_heap.Swap(0, this->m_heap.Size() - 1);
        this->m_heap.PopBack();
        this->HeapifyDown(0);

        return toPop;
    }

    template<typename typeT, typename Compare>
    bool BinaryHeap<typeT, Compare>::IsEmpty()
    {
        return this->m_heap.IsEmpty();
    }

    template<typename typeT, typename Compare>
    std::size_t BinaryHeap<typeT, Compare>::Size()
    {
        return this->m_heap.Size();
    }

    template<typename typeT, typename Compare>
    void BinaryHeap<typeT, Compare>::Clear()
    {
        this->m_heap.Clear();
    }

    template<typename typeT, typename Compare>
    void BinaryHeap<typeT, Compare>::HeapifyDown(std::size_t index)
    {
        std::size_t left    = 2 * index + 1;
        std::size_t right   = 2 * index + 2;
        std::size_t largest = index;

        if (left < this->m_heap.Size() and
            this->m_comp(this->m_heap[left], this->m_heap[largest]))
            largest = left;

        if (right < this->m_heap.Size() and
            this->m_comp(this->m_heap[right], this->m_heap[largest]))
            largest = right;

        if (largest != index)
        {
            this->m_heap.Swap(index, largest);
            this->HeapifyDown(largest);
        }
    }

    template<typename typeT, typename Compare>
    void BinaryHeap<typeT, Compare>::HeapifyUp(std::size_t index)
    {
        std::size_t parent = (index - 1) / 2;

        while (index > 0 and this->m_comp(this->m_heap[index], this->m_heap[parent]))
        {
            this->m_heap.Swap(index, parent);
            index  = parent;
            parent = (index - 1) / 2;
        }
    }

} // namespace bheap

#endif // BINARY_HEAP_H_
