#ifndef QUEUE_SINGLY_LINKED_H_
#define QUEUE_SINGLY_LINKED_H_

#include "node_singly_linked.hh"
#include "queue_excpt.hh"

// Singly linked namespace
namespace slkd {
    template <typename typeT>
    class Queue {
        private:
            Node<typeT> *_first;
            Node<typeT> *_last;
            int _size;

            /**
            @brief Deleta o primeiro nó da fila
            @throw queexcpt::QueueIsEmpty Caso a fila esteja vazia
            */
            void deleteFirst();

        public:
            Queue();

            ~Queue();

            /**
            @brief Quantidade de elementos na fila
            @return A quantidade de elementos na fila (tamanho)
            */
            int getLenght();

            /**
            @brief Enfileira um elemento
            @param element Elemento que será enfileirado
            */
            void enqueue(typeT element);

            /**
            @brief Verifica se a fila está vazia
            @return True se a fila estiver vazia, False caso contrário
            */
            bool isEmpty();

            /**
            @brief Desenfileira um elemento
            @return Primeira elemento da fila
            @throw queexcpt::QueueIsEmpty Caso a fila esteja vazia
            */
            typeT dequeue();

            /**
            @brief Remove todos os elementos da fila
            */
            void clean();
    };

    template <typename typeT>
    Queue<typeT>::Queue() {
        this->_size = 0;
        this->_first = this->_last = nullptr;
    }

    template <typename typeT>
    Queue<typeT>::~Queue() {
        this->clean();
    }

    template <typename typeT>
    int Queue<typeT>::getLenght() {
        return this->_size;
    }

    template <typename typeT>
    bool Queue<typeT>::isEmpty() {
        if (this->_size == 0) return true;
        return false;
    }

    template <typename typeT>
    void Queue<typeT>::enqueue(typeT element) {
        if (this->isEmpty()) {
            this->_first = this->_last = new Node<typeT>(element);
        }
        else {
            Node<typeT> *aux = new Node<typeT>(element);
            this->_last->_next = aux;
            this->_last = aux;
        }
        this->_size++;
    }

    template <typename typeT>
    void Queue<typeT>::deleteFirst() {
        if (this->isEmpty())
            throw queexcpt::QueueIsEmpty();

        Node<typeT> *toDelete = this->_first;
        this->_first = this->_first->_next;
        delete toDelete;
        this->_size--;
    }

    template <typename typeT>
    typeT Queue<typeT>::dequeue() {
        if (this->isEmpty())
            throw queexcpt::QueueIsEmpty();

        typeT element = this->_first->_key;
        this->deleteFirst();
        return element;
    }

    template <typename typeT>
    void Queue<typeT>::clean() {
        while (!this->isEmpty()) {
            this->deleteFirst();
        }
    }
}

#endif // QUEUE_SINGLY_LINKED_H_
