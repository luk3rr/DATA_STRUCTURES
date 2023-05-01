#ifndef STACK_H_
#define STACK_H_

#include <string>

#include "stack_excpt.hh"

#define MAX_SIZE 1000

template <typename typeT>
class Stack {
    private:
        int _top;
        typeT _v[MAX_SIZE];

    public:
        Stack();

        /**
        @brief Empilha um valor
        @param item Chave que será empilhada
        */
        void push(typeT item);

        /**
        @brief Desempilha a chave no topo da pilha
        @return Chave que foi desempilhada
        */
        typeT pop();

        /**
        @brief Retorna o elemento no topo da pilha sem desempilha-lo
        @return Chave no topo da pilha
        */
        typeT peek();

        /**
        @brief Verifica se a pilha está vazia
        @return True se a pilha estiver vazia, False caso contrário
        */
        bool isEmpty();

        /**
        @brief Remove todas as chaves da pilha
        */
        void clean();

        /**
        @brief Retorna o tamanho da pilha
        @return Inteiro com o tamanho da pilha
        */
        int getLength();
};

template<typename typeT>
Stack<typeT>::Stack() {
    this->_top = 0;
}

template<typename typeT>
void Stack<typeT>::push(typeT item) {
    this->_top++;
    this->_v[this->_top] = item;
}

template<typename typeT>
typeT Stack<typeT>::peek() {
    if (this->isEmpty()) {
        throw stkexcpt::StackIsEmpty();
    }

    return this->_v[this->_top];
}

template<typename typeT>
bool Stack<typeT>::isEmpty() {
    if (this->_top == 0) return true;
    else return false;
}

template<typename typeT>
typeT Stack<typeT>::pop() {
    if (this->isEmpty()) {
        throw stkexcpt::StackIsEmpty();
    }

    this->_top--;
    return this->_v[this->_top + 1];
}

template<typename typeT>
int Stack<typeT>::getLength() {
    return this->_top;
}

template<typename typeT>
void Stack<typeT>::clean() {
    this->_top = 0;
}

#endif // STACK_H_
