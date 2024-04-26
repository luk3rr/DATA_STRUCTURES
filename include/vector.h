/*
 * Filename: vector.h
 * Created on: June  5, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

#include "comparators.h"

// The growth factor determines how much a vector should grow when it needs to
// be resized
#define VECTOR_GROWTH_FACTOR 2
#define VECTOR_START_SIZE 8

/**
 * @brief A dynamic array-based vector class
 *
 * This class provides dynamic array functionality for storing and managing elements
 * of type 'typeT'. It allows for insertion, deletion, and various operations on
 * the elements in the vector
 *
 * @tparam typeT The type of elements stored in the vector
 */
template<typename typeT>
class Vector
{
    private:
        // Pointer to first element of vector (array)
        typeT* m_elements;
        // Total space used by vector, including elements and free space
        std::size_t m_capacity;
        // Num of elements in vector
        std::size_t m_size;

    public:
        /**
         * @brief Default constructor
         */
        Vector();

        /**
         * @brief Constructor
         * @param size Initial space allocated for the vector
         */
        Vector(const std::size_t size);

        /**
         * @brief Constructor
         * @param size Initial space allocated for the vector
         * @param value Initialization value for the elements in the vector
         */
        Vector(const std::size_t size, const typeT value);

        /**
         * @brief Construtor with initializer list to receive data as {x1, x2, x3,
         *..., xn}
         **/
        Vector(const std::initializer_list<typeT> values);

        /**
         * @brief Destructor
         */
        ~Vector();

        /**
         * @brief Copy constructor
         **/
        Vector(const Vector<typeT>& other);

        /**
         * @brief Assignment operator
         **/
        Vector& operator=(const Vector<typeT>& other);

        /**
         * @brief Overload do operador []
         * @param index Índice do elemento que será buscado
         * @return Elemento na posição index
         */
        typeT&       operator[](const std::size_t index);
        const typeT& operator[](const std::size_t index) const;

        /**
         * @brief Operator overload for ==
         * @param other Vector to be used for comparison
         * @return True if they are equal, False otherwise
         */
        bool operator==(Vector<typeT>& other);

        /**
         * @brief Get the current size of the vector
         * @return An integer representing the size of the vector
         */
        std::size_t Size() const;

        /**
         * @brief Get the current maximum size (when this limit is reached, the vector
         * is reallocated to accommodate more elements)
         * @return An integer representing the current maximum size of the vector
         */
        std::size_t GetMaxSize() const;

        /**
         * @brief Check if the vector is empty
         * @return True if the vector is empty, False otherwise
         */
        bool IsEmpty() const;

        /**
         * @brief Swap the positions of two elements
         * @param index1, index2 Positions of the elements to be swapped
         * @throw std::out_of_range If any of the indices is invalid
         */
        void Swap(const std::size_t index1, const std::size_t index2);

        /**
         * @brief Insert a new element at the end of the vector
         * @param element New element
         */
        void PushBack(const typeT element);

        /**
         * @brief Insert a new element at the specified position
         * @param pos Position to insert the new element
         * @param value New element
         */
        void Insert(const std::size_t pos, const typeT value);

        /**
         * @brief Remove the element at the end of the vector
         */
        void PopBack();

        /**
         * @brief Remove the element at the specified position
         * @param pos Position of the element to be removed
         */
        void Erase(const std::size_t pos);

        /**
         * @brief Remove the elements in the range [first, last]
         * @param first Position of the first element to be removed
         * @param last Position of the last element to be removed
         */
        void Erase(const std::size_t first, const std::size_t last);

        /**
         * @return The element at the beginning of the vector
         * @throw std::overflow_error If the vector is empty
         */
        typeT& Front() const;

        /**
         * @return The element at the end of the vector
         * @throw std::overflow_error If the vector is empty
         */
        typeT& Back() const;

        /**
         * @brief Clear the vector
         */
        void Clear();

        /**
         * @brief Resize the vector
         * @param newSize New size of the vector
         * @param val Default value for custom values when resizing
         */
        void Resize(const std::size_t newSize, const typeT val = typeT());

        /**
         * @brief Allocate a new space for this vector
         * @param newalloc Size of the new allocate
         **/
        void Reserve(const std::size_t newalloc);

        /**
         * @return The element at the specified index
         * @throw std::out_of_range If the index is invalid
         **/
        typeT&       At(const std::size_t index);
        const typeT& At(const std::size_t index) const;

        // Iterator
        using value_type = typeT;
        using pointer    = typeT*;
        using reference  = typeT&;

        typedef struct Iterator
        {
            public:
                Iterator(pointer ptr)
                    : m_ptr(ptr)
                { }

                Iterator() { }

                reference operator*() const
                {
                    return *m_ptr;
                }

                pointer operator->()
                {
                    return m_ptr;
                }

                Iterator& operator++()
                {
                    m_ptr++;
                    return *this;
                }

                Iterator operator++(int)
                {
                    Iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }

                friend bool operator==(const Iterator& a, const Iterator& b)
                {
                    return a.m_ptr == b.m_ptr;
                };

                friend bool operator!=(const Iterator& a, const Iterator& b)
                {
                    return a.m_ptr != b.m_ptr;
                };

            private:
                pointer m_ptr;

        } Iterator;

        Iterator begin()
        {
            return Iterator(&m_elements[0]);
        }

        Iterator end()
        {
            return Iterator(&m_elements[m_size]);
        }
};

template<typename typeT>
Vector<typeT>::Vector()
{
    this->m_capacity = VECTOR_START_SIZE;
    this->m_size     = 0;
    this->m_elements = new typeT[this->m_capacity];
}

template<typename typeT>
Vector<typeT>::Vector(const std::size_t size)
{
    this->m_capacity = size;
    this->m_size     = 0;
    this->m_elements = new typeT[this->m_capacity];
}

template<typename typeT>
Vector<typeT>::Vector(const std::size_t size, const typeT val)
{
    this->m_capacity = size;
    this->m_size     = size;
    this->m_elements = new typeT[this->m_capacity];

    for (std::size_t i = 0; i < size; i++)
    {
        this->m_elements[i] = val;
    }
}

template<typename typeT>
Vector<typeT>::Vector(const std::initializer_list<typeT> values)
{
    this->m_elements = new typeT[values.size()];
    this->m_capacity = values.size();
    this->m_size     = values.size();

    std::copy(values.begin(), values.end(), m_elements);
}

template<typename typeT>
Vector<typeT>::~Vector()
{
    delete[] this->m_elements;
}

template<typename typeT>
Vector<typeT>::Vector(const Vector<typeT>& other)
{
    this->m_capacity = other.m_capacity;
    this->m_size     = other.m_size;
    this->m_elements = new typeT[this->m_capacity];

    for (std::size_t i = 0; i < this->m_size; i++)
        this->m_elements[i] = other.m_elements[i];
}

template<typename typeT>
Vector<typeT>& Vector<typeT>::operator=(const Vector<typeT>& other)
{
    if (this == &other)
        return *this;

    delete[] this->m_elements;

    this->m_capacity = other.m_capacity;
    this->m_size     = other.m_size;
    this->m_elements = new typeT[this->m_capacity];

    for (std::size_t i = 0; i < this->m_size; i++)
        this->m_elements[i] = other.m_elements[i];

    return *this;
}

template<typename typeT>
typeT& Vector<typeT>::operator[](const std::size_t index)
{
    return this->m_elements[index];
}

template<typename typeT>
const typeT& Vector<typeT>::operator[](const std::size_t index) const
{
    return this->m_elements[index];
}

template<typename typeT>
bool Vector<typeT>::operator==(Vector<typeT>& other)
{
    if (this->m_size != other.Size())
        return false;

    for (std::size_t i = 0; i < this->m_size; i++)
    {
        if (this->m_elements[i] != other[i])
        {
            return false;
        }
    }

    return true;
}

template<typename typeT>
std::size_t Vector<typeT>::Size() const
{
    return this->m_size;
}

template<typename typeT>
std::size_t Vector<typeT>::GetMaxSize() const
{
    return this->m_capacity;
}

template<typename typeT>
bool Vector<typeT>::IsEmpty() const
{
    return this->m_size == 0;
}

template<typename typeT>
void Vector<typeT>::Swap(const std::size_t index1, const std::size_t index2)
{
    if (comparators::Max<std::size_t>(index1, index2) > this->m_capacity)
        throw std::out_of_range("Index out of bounds");

    typeT aux = this->m_elements[index1];

    this->m_elements[index1] = this->m_elements[index2];
    this->m_elements[index2] = aux;
}

template<typename typeT>
void Vector<typeT>::PushBack(const typeT element)
{
    if (this->m_size == this->m_capacity)
    {
        this->Reserve(this->m_capacity * VECTOR_GROWTH_FACTOR);
    }

    this->m_elements[this->m_size++] = element;
}

template<typename typeT>
void Vector<typeT>::Insert(const std::size_t pos, const typeT value)
{
    if (pos > this->m_size)
        throw std::out_of_range("Index out of bounds");

    if (this->m_size == this->m_capacity)
    {
        this->Reserve(this->m_capacity * VECTOR_GROWTH_FACTOR);
    }

    for (std::size_t i = this->m_size; i > pos; i--)
    {
        this->m_elements[i] = this->m_elements[i - 1];
    }

    this->m_elements[pos] = value;
    this->m_size++;
}

template<typename typeT>
void Vector<typeT>::PopBack()
{
    if (not this->IsEmpty())
    {
        this->m_size--;
    }
}

template<typename typeT>
void Vector<typeT>::Erase(const std::size_t pos)
{
    if (pos > this->m_size)
        throw std::out_of_range("Index out of bounds");

    for (std::size_t i = pos; i < this->m_size - 1; i++)
    {
        this->m_elements[i] = this->m_elements[i + 1];
    }

    this->m_size--;
}

template<typename typeT>
void Vector<typeT>::Erase(const std::size_t first, const std::size_t last)
{
    if (first >= this->m_size or last >= this->m_size)
        throw std::out_of_range("Index out of bounds");

    // ... + 1 because the last element is inclusive
    for (std::size_t i = first; i < this->m_size - (last - first + 1); i++)
    {
        this->m_elements[i] = this->m_elements[i + (last - first + 1)];
    }

    this->m_size -= (last - first + 1);
}

template<typename typeT>
typeT& Vector<typeT>::Front() const
{
    if (this->IsEmpty())
        throw std::overflow_error("Vector is empty");

    return m_elements[0];
}

template<typename typeT>
typeT& Vector<typeT>::Back() const
{
    if (this->IsEmpty())
        throw std::overflow_error("Vector is empty");

    return m_elements[this->m_size - 1];
}

template<typename typeT>
void Vector<typeT>::Clear()
{
    this->m_size = 0;
}

template<typename typeT>
void Vector<typeT>::Resize(std::size_t newSize, typeT val)
{
    this->Reserve(newSize);

    for (std::size_t i = this->m_size; i < newSize; ++i)
    {
        this->m_elements[i] = val;
    }

    this->m_size = newSize;
}

template<typename typeT>
void Vector<typeT>::Reserve(std::size_t newAlloc)
{

    if (newAlloc <= this->m_capacity)
        return;

    typeT* newElements = new typeT[newAlloc]();

    std::size_t i;
    for (i = 0; i < this->m_size; i++)
    {
        newElements[i] = this->m_elements[i];
    }

    delete[] this->m_elements;
    this->m_elements = newElements;
    this->m_capacity = newAlloc;
}

template<typename typeT>
typeT& Vector<typeT>::At(std::size_t index)
{
    if (index > this->m_size)
        throw std::out_of_range("Index out of bounds");

    return this->m_elements[index];
}

template<typename typeT>
const typeT& Vector<typeT>::At(std::size_t index) const
{
    if (index > this->m_size)
        throw std::out_of_range("Index out of bounds");

    return this->m_elements[index];
}

#endif // VECTOR_H_
