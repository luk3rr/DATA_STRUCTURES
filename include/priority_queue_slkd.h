/*
 * Filename: priority_queue_slkd.h
 * Created on: June 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef PRIORITY_QUEUE_SLKD_H_
#define PRIORITY_QUEUE_SLKD_H_

#include <cstddef>
#include <stdexcept>

#include "node.h"
#include "queue_base.h"

// Singly linked namespace
namespace slkd
{
    /**
     * @brief Implementation of a priority queue based on a singly linked list.
     *
     * This class implements a priority queue using a singly linked list. By default, it
     * functions as a minimum priority queue. To use it as a maximum priority queue,
     * provide a custom comparator to the Compare template parameter
     *
     * Worst-case time complexities:
     *   - Enqueue: O(n)
     *   - Dequeue: O(1)
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
            slkd::Node<typeT>* m_head;
            std::size_t        m_size;
            Compare            m_comp; // Custom comparator

            /**
             * @brief Removes the first element from the queue.
             */
            void RemoveHead();

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
             * @throw std::overflow_error If priority queue is empty
             **/
            typeT Peek() override;

            /**
             * @brief Remove and return the element with the priority value considered
             * the lowest or highest
             * @return The element with the lowest or highest priority value
             * @throw std::underflow_error If priority queue is empty
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
    {
        this->m_head = nullptr;
        this->m_size = 0;
    }

    template<typename typeT, typename Compare>
    PriorityQueue<typeT, Compare>::~PriorityQueue()
    {
        this->Clear();
    }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::Enqueue(typeT element)
    {
        slkd::Node<typeT>* newNode = new slkd::Node<typeT>(element);

        // Case 1: Insert at the beginning
        if (this->m_head == nullptr or this->m_comp(element, this->m_head->GetValue()))
        {
            newNode->SetNextNode(this->m_head);
            this->m_head = newNode;
        }
        else
        {
            slkd::Node<typeT>* current = this->m_head;

            // Case 2: Insert in the middle/end of the queue
            while (current->GetNextNode() != nullptr and
                   not m_comp(element, current->GetNextNode()->GetValue()))
                current = current->GetNextNode();

            newNode->SetNextNode(current->GetNextNode());
            current->SetNextNode(newNode);
        }

        this->m_size++;
    }

    template<typename typeT, typename Compare>
    typeT PriorityQueue<typeT, Compare>::Peek()
    {
        if (this->m_size == 0)
            throw std::overflow_error("Priority Queue is empty!");

        return this->m_head->GetValue();
    }

    template<typename typeT, typename Compare>
    typeT PriorityQueue<typeT, Compare>::Dequeue()
    {
        if (this->m_size == 0)
            throw std::underflow_error("Priority Queue is empty!");

        typeT aux = this->m_head->GetValue();
        RemoveHead();
        return aux;
    }

    template<typename typeT, typename Compare>
    bool PriorityQueue<typeT, Compare>::IsEmpty()
    {
        return (this->m_size == 0);
    }

    template<typename typeT, typename Compare>
    std::size_t PriorityQueue<typeT, Compare>::Size()
    {
        return this->m_size;
    }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::Clear()
    {
        while (not this->IsEmpty())
            this->RemoveHead();
    }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::RemoveHead()
    {
        if (this->m_head)
        {
            slkd::Node<typeT>* aux;

            aux          = this->m_head;
            this->m_head = this->m_head->GetNextNode();

            this->m_size--;
            delete aux;
        }
    }
} // namespace slkd

#endif // PRIORITY_QUEUE_SLKD_H_
