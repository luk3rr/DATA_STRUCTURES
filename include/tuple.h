/*
 * Filename: tuple.h
 * Created on: October 29, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef TUPLE_H_
#define TUPLE_H_

#include <cstddef>
#include <cstdio>

#include "tuple_excpt.h"
#include "vector.h"

/**
 * @brief Construct a Tuple with elements of different types
 *
 * This class defines a Tuple with elements of different types, where the first
 * element has type 'typeT' and the remaining elements have types specified in 'typeN'
 *
 * @tparam typeT The type of the first element
 * @tparam typeN The types of the remaining elements
 */
template<typename typeT, typename... typeN>
class Tuple : public Tuple<typeN...>
{
    private:
        typeT m_n0;

    public:
        Tuple() { }

        /**
         * @brief Constructor
         * @param n0 The value for the first element
         * @param nn The values for the remaining elements
         **/
        Tuple(typeT n0, typeN... nn)
            : Tuple<typeN...>(nn...),
              m_n0(n0)
        { }

        /**
         * @brief Emplace a value at a specified index
         *
         * @tparam index The index where the value should be emplaced
         * @param value The value to emplace
         */
        template<std::size_t index, typename T>
        void Emplace(T value)
        {
            if constexpr (index == 0)
            {
                m_n0 = value;
            }
            else
            {
                Tuple<typeN...>::template Emplace<index - 1, T>(value);
            }
        }

        template<std::size_t index, typename, typename...>
        friend class ValueAt;
};

/**
 * @brief Construct a Tuple with elements of the same type
 * @tparam typeT The type of all elements
 */
template<typename typeT>
class Tuple<typeT>
{
    private:
        typeT m_n0;

    public:
        Tuple() { }

        /**
         * @brief  Constructor
         * @param n0 The value for the first element
         **/
        Tuple(typeT n0)
            : m_n0(n0)
        { }

        /**
         * @brief Emplace a value at a specified index.
         * @tparam typeTT The type of the value
         * @tparam index The index where the value should be emplaced.
         * @param value The value to emplace.
         */
        template<std::size_t index, typename typeTT>
        void Emplace(typeTT value)
        {
            if constexpr (index == 0)
            {
                m_n0 = value;
            }
        }

        template<std::size_t index, typename, typename...>
        friend class ValueAt;
};

/**
 * @brief Get the value at a specified index using metaprogramming
 * @tparam index The index of the value to retrieve
 * @tparam typeT The type of the first element
 * @tparam typeN The types of the remaining elements
 * @param t Pointer to the Tuple object
 * @return The value at the specified index
 */
template<std::size_t index, typename typeT, typename... typeN>
class ValueAt
{
    public:
        static auto Value(const Tuple<typeT, typeN...>* t)
            -> decltype(ValueAt<index - 1, typeN...>::Value(t))
        {
            return ValueAt<index - 1, typeN...>::Value(t);
        }
};

/**
 * @brief Get the value at index 0 using metaprogramming
 * @tparam index The index of the value to retrieve
 * @tparam typeT The type of the first element
 * @tparam typeN The types of the remaining elements
 * @param t Pointer to the Tuple object
 * @return The value at index 0
 */
template<typename typeT, typename... typeN>
class ValueAt<0, typeT, typeN...>
{
    public:
        static typeT Value(const Tuple<typeT, typeN...>* t)
        {
            return t->m_n0;
        }
};

/**
 * @brief Emplace a value at a specified index in a Tuple
 * @tparam index The index where the value should be emplaced
 * @tparam typeT The type of the first element
 * @tparam typeN The types of the remaining elements
 * @param t Reference to the Tuple object
 * @param value The value to emplace
 */
template<std::size_t index, typename typeT, typename... typeN>
void Emplace(Tuple<typeT, typeN...>& t, typeT value)
{
    t.template Emplace<index>(value);
}

/**
 * @brief Get the value at a specified index in a Tuple using metaprogramming
 * @tparam index The index of the value to retrieve
 * @tparam typeT The type of the first element
 * @tparam typeN The types of the remaining elements
 * @param t Reference to the Tuple object
 * @return The value at the specified index
 */
template<std::size_t index, typename typeT, typename... typeN>
auto Get(const Tuple<typeT, typeN...>& t)
    -> decltype(ValueAt<index, typeT, typeN...>::Value(&t))
{
    return ValueAt<index, typeT, typeN...>::Value(&t);
}

#endif // TUPLE_H_
