/*
* Filename: vector.h
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef VECTOR_H_
#define VECTOR_H_

#include "utils.h"
#include "vector_excpt.h"
#include <cstddef>

#define VECTOR_START_SIZE 8
// The growth factor determines how much a vector should grow when it needs to be resized
#define VECTOR_GROWTH_FACTOR 2


// TODO implementar funções: insert(pos, valor), erase(pos)

template<typename typeT>
class Vector {
    private:
        typeT *m_elements; // Pointer to first element of vector (array)
        std::size_t m_capacity; // Total space used by vector, including elements and free space
        std::size_t m_size; // Num of elements in vector

    public:
        /**
        @brief Construtor padrão da classe
        */
        Vector();

        /**
        @brief Destrutor da classe
        */
        ~Vector();

        /**
        @brief Overload do operador []
        @param index Índice do elemento que será buscado
        @return Elemento na posição index
        @throw InvalidIndex Caso o índice seja inválido
        */
        typeT &operator[](std::size_t index);

        /**
        @brief Overload do operador ==
        @param other Vetor que será usado na verificação
        @return True se forem iguais, False caso contrário
        */
        bool operator==(Vector<typeT> &other);

        /**
        @brief Pega o tamanho atual do vector
        @return Inteiro que representa o tamanho do vector
        */
        std::size_t Size();

        /**
        @brief Pega o tamanho máximo atual (quando esse limite for alcança o vector é realocado para comportar mais elementos)
        @return Inteiro que representa o tamanho máximo atual do vector
        */
        std::size_t GetMaxSize();

        /**
        @brief Verifica se o vector está vazio
        @return True se o vector estiver vazio, False caso contrário
        */
        bool IsEmpty();

        /**
        @brief Troca a posição de dois elementos
        @param index1, index2 Posições dos elementos que serão trocados de posição
        @throw InvalidIndex Caso algum dos índice seja inválido
        */
        void Swap(std::size_t index1, std::size_t index2);

        /**
        @brief Insere um novo elemento no fim do vector
        @param element Novo elemento
        */
        void PushBack(typeT element);

        /**
        @brief Remove o elemento que está no fim do vector
        */
        void PopBack();

        /**
        @brief Limpa o vector
        */
        void Clear();

        /**
         * @brief Resize the vector
         * @param newSize New size of the vector
         * @param val Default value for custom values when resizing
         */
        void Resize(std::size_t newSize, typeT val = typeT());

        /**
         * @brief Allocate a new space for this vector
         * @param newalloc Size of the new allocate
         **/
        void Reserve(std::size_t newalloc);

        /**
         * @return The element at the specified index
         **/
        typeT &At(std::size_t index);

        // Implementação do iterator
        using value_type = typeT;
        using pointer = typeT *;
        using reference = typeT &;

        typedef struct Iterator {
            public:
                Iterator(pointer ptr) : m_ptr(ptr) { }

                Iterator() { }

                reference operator*() const {
                    return *m_ptr;
                }

                pointer operator->() {
                    return m_ptr;
                }

                Iterator &operator++() {
                    m_ptr++;
                    return *this;
                }

                Iterator operator++(int) {
                    Iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }

                friend bool operator==(const Iterator &a, const Iterator &b) {
                    return a.m_ptr == b.m_ptr;
                };

                friend bool operator!=(const Iterator &a, const Iterator &b) {
                    return a.m_ptr != b.m_ptr;
                };

            private:
                pointer m_ptr;

        } Iterator;

    Iterator begin() {
        return Iterator(&m_elements[0]);
    }

    Iterator end() {
        return Iterator(&m_elements[m_size]);
    }
};

template<typename typeT>
Vector<typeT>::Vector() {
    this->m_capacity = VECTOR_START_SIZE;
    this->m_size = 0;
    this->m_elements = new typeT[this->m_capacity];
}

template<typename typeT>
Vector<typeT>::~Vector() {
    delete[] this->m_elements;
}

template<typename typeT>
typeT &Vector<typeT>::operator[](std::size_t index) {
    return this->m_elements[index];
}

template<typename typeT>
bool Vector<typeT>::operator==(Vector<typeT> &other) {
    if (this->m_size != other.Size())
        return false;

    for (std::size_t i = 0; i < this->m_size; i++) {
        if (this->m_elements[i] != other[i]) {
            return false;
        }
    }

    return true;
}

template<typename typeT>
std::size_t Vector<typeT>::Size() {
    return this->m_size;
}

template<typename typeT>
std::size_t Vector<typeT>::GetMaxSize() {
    return this->m_capacity;
}

template<typename typeT>
bool Vector<typeT>::IsEmpty() {
    return this->m_size == 0;
}

template<typename typeT>
void Vector<typeT>::Swap(std::size_t index1, std::size_t index2) {
    if ((std::size_t)utils::Max(index1, index2) > this->m_capacity)
        throw vecexcpt::InvalidIndex();

    typeT aux = this->m_elements[index1];
    this->m_elements[index1] = this->m_elements[index2];
    this->m_elements[index2] = aux;
}

template<typename typeT>
void Vector<typeT>::PushBack(typeT element) {
    if (this->m_size == this->m_capacity) {
        this->Reserve(this->m_capacity * VECTOR_GROWTH_FACTOR);
    }

    this->m_elements[this->m_size++] = element;
}

template<typename typeT>
void Vector<typeT>::PopBack() {
    if (not this->IsEmpty()) {
        this->m_size--;
    }
}

template<typename typeT>
void Vector<typeT>::Clear() {
    this->m_size = 0;
}

template<typename typeT>
void Vector<typeT>::Resize(std::size_t newSize, typeT val) {
    this->Reserve(newSize);

    for (std::size_t i = this->m_size; i < newSize; ++i) {
        this->m_elements[i] = typeT();
    }

    this->m_size = newSize;
}

template<typename typeT>
void Vector<typeT>::Reserve(std::size_t newAlloc) {

    if (newAlloc <= this->m_capacity)
        return;

    typeT *newElements = new typeT[newAlloc]();

    std::size_t i;
    for (i = 0; i < this->m_size; i++) {
        newElements[i] = this->m_elements[i];
    }

    delete[] this->m_elements;
    this->m_elements = newElements;
    this->m_capacity = newAlloc;
}

template<typename typeT>
typeT &Vector<typeT>::At(std::size_t index) {
    if (index > this->m_size)
        throw vecexcpt::InvalidIndex();

    return this->m_elements[index];
}

#endif // VECTOR_H_
