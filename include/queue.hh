#ifndef QUEUE_H_
#define QUEUE_H_

#include "queue_excpt.hh"

#define QUEUE_MAX_SIZE 1000

template <typename typeT>
class CircularQueue {
    private:
        int _lenght, _front, _back;
        typeT _fila[QUEUE_MAX_SIZE];

    public:
        CircularQueue();

        /**
        @brief Tamanho o elemento no topo da fila
        @return Inteiro com o tamanho da fila
        */
        int getLength();

        /**
        @brief Enfileira um elemento
        @param item Chave que será enfileirada
        */
        void enqueue(typeT item);

        /**
        @brief Desenfileira um elemento
        @return Elemento que foi desenfileirado
        */
        typeT dequeue();

        /**
        @brief Verifica se a fila está vazia
        @return True se a fila estiver vazia, False caso contrário
        */
        bool isEmpty();

        /**
        @brief Remove todos os elementos da fila
        */
        void clean();
};

template <typename typeT>
CircularQueue<typeT>::CircularQueue() {
    this->_lenght = 0;
    this->_front = 0;
    this->_back = 0;
}

template <typename typeT>
int CircularQueue<typeT>::getLength() {
    return this->_lenght;
}

template <typename typeT>
bool CircularQueue<typeT>::isEmpty() {
    if (this->_lenght == 0) return true;
    else return false;
}

// Adiciona um item ao fim da fila
template <typename typeT>
void CircularQueue<typeT>::enqueue(typeT item) {
    if (this->_lenght == QUEUE_MAX_SIZE)
        throw queexcpt::QueueOverflow();

    this->_fila[this->_back] = item;
    this->_back = (this->_back + 1) % QUEUE_MAX_SIZE;
    this->_lenght++;
}

// Remove o primeiro item da fila
template <typename typeT>
typeT CircularQueue<typeT>::dequeue() {
    if (this->_lenght == 0)
        throw queexcpt::QueueIsEmpty();

    typeT element = this->_fila[this->_front];
    this->_front = (this->_front + 1) % QUEUE_MAX_SIZE;
    this->_lenght--;
    return element;
}

// Limpa a fila
template <typename typeT>
void CircularQueue<typeT>::clean() {
    this->_lenght = 0;
    this->_front = 0;
    this->_back = 0;
}

#endif // QUEUE_H_
