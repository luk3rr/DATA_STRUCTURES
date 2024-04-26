/*
 * Filename: comparators.h
 * Created on: April 16, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef COMPARATORS_H_
#define COMPARATORS_H_

#include "pair.h"

namespace comparators
{
    /**
     * @brief A function object to compare two values using less-than operator
     */
    template<typename typeT>
    auto less = [](const typeT& a, const typeT& b) -> bool { return a < b; };

    /**
     * @brief A function object to compare two values using greater-than operator
     */
    template<typename typeT>
    auto greater = [](const typeT& a, const typeT& b) -> bool { return a > b; };

    /**
     * @brief A function object to compare two values for equality
     */
    template<typename typeT>
    auto equal = [](const typeT& a, const typeT& b) -> bool { return a == b; };

    /**
     * @brief Custom 'less than' comparator for the Pair class. Used only in the context
     * of the map to manipulate elements in the red-black tree.
     *
     * Considers a < b if a.key < b.key.
     *
     * @tparam typeK The type of the value stored in the key of the Pair
     * @tparam typeV The type of the value stored in the value of the Pair
     */
    template<typename typeK, typename typeV>
    auto pairLess =
        [](const Pair<typeK, typeV>& a, const Pair<typeK, typeV>& b) -> bool {
        return a.GetFirst() < b.GetFirst();
    };

    /**
     * @brief Custom 'equal to' comparator for the Pair class. Used only in the context
     * of the map to manipulate elements in the red-black tree.
     *
     * Considers a == b if a.key == b.key.
     *
     * @tparam typeK The type of the value stored in the key of the Pair
     * @tparam typeV The type of the value stored in the value of the Pair
     */
    template<typename typeK, typename typeV>
    auto pairEqual =
        [](const Pair<typeK, typeV>& a, const Pair<typeK, typeV>& b) -> bool {
        return a.GetFirst() == b.GetFirst();
    };

} // namespace comparators

#endif // COMPARATORS_H_
