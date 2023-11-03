/*
 * Filename: priority_queue_bheap.h
 * Created on: July  9, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef PRIORITY_QUEUE_BHEAP_H_
#define PRIORITY_QUEUE_BHEAP_H_

#include "queue_base.h"
#include "queue_excpt.h"
#include "vector.h"
#include <cstddef>

// Binary heap namespace
namespace bheap
{
    /**
     * @brief Implementation of a priority queue on top of a binary heap structure
     *
     * This class implements a priority queue using a binary heap. By default, it
     * functions as a minimum priority queue. To use it as a maximum priority queue,
     * provide a custom comparator to the Compare template parameter
     *
     * Worst-case time complexities:
     *   - Enqueue: O(1 + log n) where log n is the execution time of HeapifyDown
     *   - Dequeue: O(1 + log n) where log n is the execution time of HeapifyUp
     *   - Peek: O(1)
     *
     * @tparam typeT The type of elements stored in the priority queue
     * @tparam Compare The custom comparator used to determine the priority of elements
     *
     * NOTE: By default, the 'Compare' parameter is set to 'utils::less<typeT>' for a
     * minimum priority queue
     */
    template<typename typeT, typename Compare = utils::less<typeT>>
    class PriorityQueue : public QueueBase<typeT>
    {
        private:
            Vector<typeT> m_heap;
            Compare       m_comp; // Custom comparator

            /**
             * @brief Adjusts the heap after the removal of an element
             * @param index Index of the removed element
             **/
            void HeapifyDown(unsigned int index);

            /**
             * @brief Adjusts the heap after the insertion of an element
             * @param index Index of the inserted element
             **/
            void HeapifyUp(unsigned int index);

        public:
            /**
             * @brief Constructor for PriorityQueue
             * @param comp The custom comparator to use (default is the standard
             * comparator)
             */
            PriorityQueue(const Compare& comp = Compare());

            ~PriorityQueue();

            /**
             * @brief Insert a new element into the queue
             * @param element New element
             **/
            void Enqueue(typeT element) override;

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
            typeT Dequeue() override;

            /**
             * @brief Check if the queue is empty
             * @return True if it is empty, False otherwis
             **/
            bool IsEmpty() override;

            /**
             * @brief Get the current size of the queue
             * @return The current size of the queue
             **/
            std::size_t Size() override;

            /**
             * @brief Delete all nodes in the queue
             **/
            void Clear() override;
    };

    template<typename typeT, typename Compare>
    PriorityQueue<typeT, Compare>::PriorityQueue(const Compare& comp)
        : m_comp(comp)
    { }

    template<typename typeT, typename Compare>
    PriorityQueue<typeT, Compare>::~PriorityQueue()
    { }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::HeapifyDown(unsigned int index)
    {
        unsigned int left    = 2 * index + 1;
        unsigned int right   = 2 * index + 2;
        unsigned int largest = index;

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
    void PriorityQueue<typeT, Compare>::HeapifyUp(unsigned int index)
    {
        unsigned int parent = (index - 1) / 2;

        while (index > 0 and this->m_comp(this->m_heap[index], this->m_heap[parent]))
        {
            this->m_heap.Swap(index, parent);
            index  = parent;
            parent = (index - 1) / 2;
        }
    }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::Enqueue(typeT element)
    {
        this->m_heap.PushBack(element);
        this->HeapifyUp(this->m_heap.Size() - 1);
    }

    template<typename typeT, typename Compare>
    typeT PriorityQueue<typeT, Compare>::Peek()
    {
        if (this->m_heap.IsEmpty())
            throw queexcpt::QueueIsEmpty();

        return this->m_heap[0];
    }

    template<typename typeT, typename Compare>
    typeT PriorityQueue<typeT, Compare>::Dequeue()
    {
        if (this->m_heap.IsEmpty())
            throw queexcpt::QueueIsEmpty();

        typeT max = this->m_heap[0];
        this->m_heap.Swap(0, this->m_heap.Size() - 1);
        this->m_heap.PopBack();
        this->HeapifyDown(0);

        return max;
    }

    template<typename typeT, typename Compare>
    bool PriorityQueue<typeT, Compare>::IsEmpty()
    {
        return this->m_heap.IsEmpty();
    }

    template<typename typeT, typename Compare>
    std::size_t PriorityQueue<typeT, Compare>::Size()
    {
        return this->m_heap.Size();
    }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::Clear()
    {
        this->m_heap.Clear();
    }
} // namespace bheap

#endif // PRIORITY_QUEUE_BHEAP_H_
