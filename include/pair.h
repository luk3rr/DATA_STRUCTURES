/*
 * Filename: pair.h
 * Created on: June 28, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef PAIR_H_
#define PAIR_H_

#include <ostream>

/**
 * @brief A templated class representing a pair of values
 *
 * This class template represents a pair of values, where 'typeK' is the type of
 * the key, and 'typeV' is the type of the value
 *
 * @tparam typeK The type of the key
 * @tparam typeV The type of the value
 */
template<typename typeK, typename typeV>
class Pair
{
    private:
        typeK m_key;
        typeV m_value;

    public:
        /**
         * @brief Default constructor
         **/
        Pair();

        Pair(const typeK& key, const typeV& value);

        /**
         * @brief Copy constructor
         **/
        Pair(const Pair<typeK, typeV>& other);

        ~Pair();

        /**
         * @brief Assignment operator
         **/
        Pair<typeK, typeV>& operator=(const Pair<typeK, typeV>& other);

        /**
         * @brief Overloaded output stream operator to print the Pair
         * @param os The output stream
         * @return The modified output stream
         */
        std::ostream& operator<<(std::ostream& os);

        /**
         * @brief Set a new key
         * @param key The value of the new key
         */
        void SetFirst(const typeK& key);

        /**
         * @brief Set a new value
         * @param value The value of the new value
         */
        void SetSecond(const typeV& value);

        /**
         * @return The key
         */
        typeK& GetFirst();
        typeK  GetFirst() const;

        /**
         * @return The value
         */
        typeV& GetSecond();
        typeV  GetSecond() const;
};

template<typename typeK, typename typeV>
Pair<typeK, typeV>::Pair()
{
    this->m_key   = typeK();
    this->m_value = typeV();
}

template<typename typeK, typename typeV>
Pair<typeK, typeV>::Pair(const typeK& key, const typeV& value)
{
    this->m_key   = key;
    this->m_value = value;
}

template<typename typeK, typename typeV>
Pair<typeK, typeV>::Pair(const Pair<typeK, typeV>& other)
{
    this->m_key   = other.m_key;
    this->m_value = other.m_value;
}

template<typename typeK, typename typeV>
Pair<typeK, typeV>::~Pair()
{ }

template<typename typeK, typename typeV>
Pair<typeK, typeV>& Pair<typeK, typeV>::operator=(const Pair<typeK, typeV>& other)
{
    if (this != &other)
    {
        m_key   = other.m_key;
        m_value = other.m_value;
    }
    return *this;
}

template<typename typeK, typename typeV>
std::ostream& Pair<typeK, typeV>::operator<<(std::ostream& os)
{
    os << "{" << m_key << ", " << m_value << "}";
    return os;
}

template<typename typeK, typename typeV>
void Pair<typeK, typeV>::SetFirst(const typeK& key)
{
    this->m_key = key;
}

template<typename typeK, typename typeV>
void Pair<typeK, typeV>::SetSecond(const typeV& value)
{
    this->m_value = value;
}

template<typename typeK, typename typeV>
typeK& Pair<typeK, typeV>::GetFirst()
{
    return this->m_key;
}

template<typename typeK, typename typeV>
typeK Pair<typeK, typeV>::GetFirst() const
{
    return this->m_key;
}

template<typename typeK, typename typeV>
typeV& Pair<typeK, typeV>::GetSecond()
{
    return this->m_value;
}

template<typename typeK, typename typeV>
typeV Pair<typeK, typeV>::GetSecond() const
{
    return this->m_value;
}

#endif // PAIR_H_
