/*
* Filename: stack_slkd.h
* Created on: May 14, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef STACK_SLKD_H_
#define STACK_SLKD_H_

#include "node_slkd.h"
#include "stack_excpt.h"

// Singly linked namespace
namespace slkd {
    template <typename typeT>
    class Stack {
        private:
            Node<typeT> *m_bottom;
            Node<typeT> *m_top;
            int m_size;

            /**
            @brief Deleta o primeiro nó da pilha
            @throw queexcpt::StackIsEmpty Caso a pilha esteja vazia
            */
            void DeleteTop();

        public:
            Stack();

            ~Stack();

            /**
            @brief Quantidade de elementos na pilha
            @return A quantidade de elementos na pilha (tamanho)
            */
            int Size();

            /**
            @brief Retorna o elemento no topo da pilha sem desempilha-lo
            @return Chave no topo da pilha
            */
            typeT Peek();

            /**
            @brief Empilha um elemento
            @param element Elemento que será enfileirado
            */
            void Push(typeT element);

            /**
            @brief Verifica se a pilha está vazia
            @return True se a pilha estiver vazia, False caso contrário
            */
            bool IsEmpty();

            /**
            @brief Desempilha um elemento
            @return Primeira elemento da pilha
            @throw queexcpt::StackIsEmpty Caso a pilha esteja vazia
            */
            typeT Pop();

            /**
            @brief Remove todos os elementos da pilha
            */
            void Clear();
    };

    template <typename typeT>
    Stack<typeT>::Stack() {
        this->m_size = 0;
        this->m_bottom = this->m_top = nullptr;
    }

    template <typename typeT>
    Stack<typeT>::~Stack() {
        this->Clear();
    }

    template <typename typeT>
    int Stack<typeT>::Size() {
        return this->m_size;
    }

    template <typename typeT>
    typeT Stack<typeT>::Peek() {
        if (this->IsEmpty())
            throw stkexcpt::StackIsEmpty();

        return this->m_top->m_key;
    }

    template <typename typeT>
    bool Stack<typeT>::IsEmpty() {
        if (this->m_size == 0) return true;
        return false;
    }

    template <typename typeT>
    void Stack<typeT>::Push(typeT element) {
        if (this->IsEmpty()) {
            this->m_bottom = this->m_top = new Node<typeT>(element);
        }
        else {
            Node<typeT> *aux = new Node<typeT>(element);
            aux->m_next = this->m_top;
            this->m_top = aux;
        }
        this->m_size++;
    }

    template <typename typeT>
    void Stack<typeT>::DeleteTop() {
        if (this->IsEmpty())
            throw stkexcpt::StackIsEmpty();

        Node<typeT> *toDelete = this->m_top;
        this->m_top = this->m_top->m_next;
        delete toDelete;
        this->m_size--;
    }

    template <typename typeT>
    typeT Stack<typeT>::Pop() {
        if (this->IsEmpty())
            throw stkexcpt::StackIsEmpty();

        typeT element = this->m_top->m_key;
        this->DeleteTop();
        return element;
    }

    template <typename typeT>
    void Stack<typeT>::Clear() {
        while (!this->IsEmpty()) {
            this->DeleteTop();
        }
    }
}

#endif // STACK_SLKD_H_
