/*
 * Filename: stack_slkd.h
 * Created on: May 14, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef STACK_SLKD_H_
#define STACK_SLKD_H_

#include <cstddef>
#include <stdexcept>

#include "node.h"

// Singly linked namespace
namespace slkd
{
    /**
     * @brief Implementation of a stack using a singly-linked list
     *
     * This class implements a stack data structure on top of a singly-linked list. It
     * provides efficient push, pop, peek, and other stack operations
     *
     * Implementation with worst-case time complexities:
     * - Push: O(1)
     * - Pop: O(1)
     * - Peek: O(1)
     *
     * @tparam typeT The type of elements stored in the stack
     */
    template<typename typeT>
    class Stack
    {
        private:
            Node<typeT>* m_bottom;
            Node<typeT>* m_top;
            std::size_t  m_size;

            /**
             * @brief Deletes the top element of the stack.
             * @throw std::underflow_error If the stack is empty.
             */
            void DeleteTop();

        public:
            Stack();

            ~Stack();

            /**
             * @brief Push an element onto the stack
             * @param element Element to be pushed onto the stack
             */
            void Push(typeT element);

            /**
             * @brief Return the element at the top of the stack without popping it
             * @return The element at the top of the stack
             * @throw std::overflow_error If the stack is empty.
             */
            typeT Peek();

            /**
             * @brief Pop an element from the stack
             * @return The element at the top of the stack
             * @throw std::underflow_error If the stack is empty.
             */
            typeT Pop();

            /**
             * @brief Check if the stack is empty
             * @return True if the stack is empty, false otherwise
             */
            bool IsEmpty();

            /**
             * @brief Get the number of elements in the stack
             * @return The number of elements in the stack (size)
             */
            std::size_t Size();

            /**
             * @brief Remove all elements from the stack
             */
            void Clear();
    };

    template<typename typeT>
    Stack<typeT>::Stack()
    {
        this->m_size   = 0;
        this->m_bottom = this->m_top = nullptr;
    }

    template<typename typeT>
    Stack<typeT>::~Stack()
    {
        this->Clear();
    }

    template<typename typeT>
    void Stack<typeT>::Push(typeT element)
    {
        if (this->IsEmpty())
        {
            this->m_bottom = this->m_top = new Node<typeT>(element);
        }
        else
        {
            Node<typeT>* aux = new Node<typeT>(element);
            aux->SetNextNode(this->m_top);
            this->m_top = aux;
        }

        this->m_size++;
    }

    template<typename typeT>
    typeT Stack<typeT>::Peek()
    {
        if (this->IsEmpty())
            throw std::overflow_error("Stack is empty!");

        return this->m_top->GetValue();
    }

    template<typename typeT>
    typeT Stack<typeT>::Pop()
    {
        if (this->IsEmpty())
            throw std::underflow_error("Stack is empty!");

        typeT element = this->m_top->GetValue();
        this->DeleteTop();
        return element;
    }

    template<typename typeT>
    bool Stack<typeT>::IsEmpty()
    {
        return (this->m_size == 0);
    }

    template<typename typeT>
    std::size_t Stack<typeT>::Size()
    {
        return this->m_size;
    }

    template<typename typeT>
    void Stack<typeT>::Clear()
    {
        while (not this->IsEmpty())
        {
            this->DeleteTop();
        }
    }

    template<typename typeT>
    void Stack<typeT>::DeleteTop()
    {
        if (this->IsEmpty())
            throw std::underflow_error("Stack is empty!");

        Node<typeT>* toDelete = this->m_top;
        this->m_top           = this->m_top->GetNextNode();
        delete toDelete;
        this->m_size--;
    }
} // namespace slkd

#endif // STACK_SLKD_H_
