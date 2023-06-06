/*
* Filename: stack.h
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef STACK_H_
#define STACK_H_

#include <string>

#include "stack_excpt.h"

#define STACK_MAX_SIZE 1000

template <typename typeT>
class Stack {
    private:
        int m_top;
        typeT m_array[STACK_MAX_SIZE];

    public:
        Stack();

        /**
        @brief Empilha um valor
        @param item Chave que será empilhada
        */
        void Push(typeT item);

        /**
        @brief Desempilha a chave no topo da pilha
        @return Chave que foi desempilhada
        */
        typeT Pop();

        /**
        @brief Retorna o elemento no topo da pilha sem desempilha-lo
        @return Chave no topo da pilha
        */
        typeT Peek();

        /**
        @brief Verifica se a pilha está vazia
        @return True se a pilha estiver vazia, False caso contrário
        */
        bool IsEmpty();

        /**
        @brief Remove todas as chaves da pilha
        */
        void Clear();

        /**
        @brief Retorna o tamanho da pilha
        @return Inteiro com o tamanho da pilha
        */
        int Size();
};

template<typename typeT>
Stack<typeT>::Stack() {
    this->m_top = 0;
}

template<typename typeT>
void Stack<typeT>::Push(typeT item) {
    if (this->m_top == STACK_MAX_SIZE)
        throw stkexcpt::StackOverflow();

    this->m_top++;
    this->m_array[this->m_top] = item;
}

template<typename typeT>
typeT Stack<typeT>::Peek() {
    if (this->IsEmpty())
        throw stkexcpt::StackIsEmpty();

    return this->m_array[this->m_top];
}

template<typename typeT>
bool Stack<typeT>::IsEmpty() {
    if (this->m_top == 0) return true;
    else return false;
}

template<typename typeT>
typeT Stack<typeT>::Pop() {
    if (this->IsEmpty())
        throw stkexcpt::StackIsEmpty();

    this->m_top--;
    return this->m_array[this->m_top + 1];
}

template<typename typeT>
int Stack<typeT>::Size() {
    return this->m_top;
}

template<typename typeT>
void Stack<typeT>::Clear() {
    this->m_top = 0;
}

#endif // STACK_H_
