#ifndef STACK_SINGLY_LINKED_H_
#define STACK_SINGLY_LINKED_H_

#include "node_singly_linked.hh"
#include "stack_excpt.hh"

// Singly linked namespace
namespace slkd {
    template <typename typeT>
    class Stack {
        private:
            Node<typeT> *_bottom;
            Node<typeT> *_top;
            int _size;

            /**
            @brief Deleta o primeiro nó da pilha
            @throw queexcpt::StackIsEmpty Caso a pilha esteja vazia
            */
            void deleteTop();

        public:
            Stack();

            ~Stack();

            /**
            @brief Quantidade de elementos na pilha
            @return A quantidade de elementos na pilha (tamanho)
            */
            int getLenght();

            /**
            @brief Retorna o elemento no topo da pilha sem desempilha-lo
            @return Chave no topo da pilha
            */
            typeT peek();

            /**
            @brief Empilha um elemento
            @param element Elemento que será enfileirado
            */
            void push(typeT element);

            /**
            @brief Verifica se a pilha está vazia
            @return True se a pilha estiver vazia, False caso contrário
            */
            bool isEmpty();

            /**
            @brief Desempilha um elemento
            @return Primeira elemento da pilha
            @throw queexcpt::StackIsEmpty Caso a pilha esteja vazia
            */
            typeT pop();

            /**
            @brief Remove todos os elementos da pilha
            */
            void clean();
    };

    template <typename typeT>
    Stack<typeT>::Stack() {
        this->_size = 0;
        this->_bottom = this->_top = nullptr;
    }

    template <typename typeT>
    Stack<typeT>::~Stack() {
        this->clean();
    }

    template <typename typeT>
    int Stack<typeT>::getLenght() {
        return this->_size;
    }

    template <typename typeT>
    typeT Stack<typeT>::peek() {
        if (this->isEmpty())
            throw stkexcpt::StackIsEmpty();

        return this->_top->_key;
    }

    template <typename typeT>
    bool Stack<typeT>::isEmpty() {
        if (this->_size == 0) return true;
        return false;
    }

    template <typename typeT>
    void Stack<typeT>::push(typeT element) {
        if (this->isEmpty()) {
            this->_bottom = this->_top = new Node<typeT>(element);
        }
        else {
            Node<typeT> *aux = new Node<typeT>(element);
            aux->_next = this->_top;
            this->_top = aux;
        }
        this->_size++;
    }

    template <typename typeT>
    void Stack<typeT>::deleteTop() {
        if (this->isEmpty())
            throw stkexcpt::StackIsEmpty();

        Node<typeT> *toDelete = this->_top;
        this->_top = this->_top->_next;
        delete toDelete;
        this->_size--;
    }

    template <typename typeT>
    typeT Stack<typeT>::pop() {
        if (this->isEmpty())
            throw stkexcpt::StackIsEmpty();

        typeT element = this->_top->_key;
        this->deleteTop();
        return element;
    }

    template <typename typeT>
    void Stack<typeT>::clean() {
        while (!this->isEmpty()) {
            this->deleteTop();
        }
    }
}

#endif // STACK_SINGLY_LINKED_H_
