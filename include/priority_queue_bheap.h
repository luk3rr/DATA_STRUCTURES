/*
 * Filename: priority_queue_bheap.h
 * Created on: July  9, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef PRIORITY_QUEUE_BHEAP_H_
#define PRIORITY_QUEUE_BHEAP_H_

#include <cstddef>
#include <stdexcept>

#include "binary_heap.h"
#include "comparators.h"
#include "queue_base.h"

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
     * NOTE: By default, the 'Compare' parameter is set to 'comparators::Less<typeT>' for a
     * minimum priority queue
     */
    template<typename typeT, typename Compare = decltype(comparators::Less<typeT>)>
    class PriorityQueue : public QueueBase<typeT>, public BinaryHeap<typeT, Compare>
    {
        private:
            using BHeap = BinaryHeap<typeT, Compare>;

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
             * @throw std::overflow_error If queue is empty
             **/
            typeT Peek() override;

            /**
             * @brief Remove and return the element with the priority value considered
             * the lowest or highest
             * @return The element with the lowest or highest priority value
             * @throw std::underflow_error If queue is empty
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
        : BinaryHeap<typeT, Compare>(comp)
    { }

    template<typename typeT, typename Compare>
    PriorityQueue<typeT, Compare>::~PriorityQueue()
    { }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::Enqueue(typeT element)
    {
        BHeap::Push(element);
    }

    template<typename typeT, typename Compare>
    typeT PriorityQueue<typeT, Compare>::Peek()
    {
        if (BHeap::IsEmpty())
            throw std::overflow_error("Queue is empty!");

        return BHeap::Peek();
    }

    template<typename typeT, typename Compare>
    typeT PriorityQueue<typeT, Compare>::Dequeue()
    {
        if (BHeap::IsEmpty())
            throw std::underflow_error("Queue is empty!");

        return BHeap::Pop();
    }

    template<typename typeT, typename Compare>
    bool PriorityQueue<typeT, Compare>::IsEmpty()
    {
        return BHeap::IsEmpty();
    }

    template<typename typeT, typename Compare>
    std::size_t PriorityQueue<typeT, Compare>::Size()
    {
        return BHeap::Size();
    }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::Clear()
    {
        return BHeap::Clear();
    }
} // namespace bheap

#endif // PRIORITY_QUEUE_BHEAP_H_
