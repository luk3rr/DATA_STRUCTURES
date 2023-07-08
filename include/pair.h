/*
* Filename: pair.h
* Created on: June 28, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef PAIR_H_
#define PAIR_H_

template<typename typeK, typename typeV>
class Pair {
    private:
        typeK m_key;
        typeV m_value;

    public:
        Pair(const typeK &key, const typeV &value);

        /**
         * @brief Define uma nova chave
         * @param key Valor da nova chave
         **/
        void SetKey(const typeK &key);

        /**
         * @brief Define um novo valor
         * @param value Valor do novo valor
         **/
        void SetValue(const typeV &value);

        /**
         * @brief Pega a chave
         * @param A chave
         **/
        typeK &GetKey();

        /**
         * @brief Pega o valor
         * @param O valor
         **/
        typeV &GetValue();
};

template<typename typeK, typename typeV>
Pair<typeK, typeV>::Pair(const typeK &key, const typeV &value) {
    this->m_key = key;
    this->m_value = value;
}

template<typename typeK, typename typeV>
void Pair<typeK, typeV>::SetKey(const typeK &key) {
    this->m_key = key;
}

template<typename typeK, typename typeV>
void Pair<typeK, typeV>::SetValue(const typeV &value) {
    this->m_value = value;
}

template<typename typeK, typename typeV>
typeK &Pair<typeK, typeV>::GetKey() {
    return this->m_key;
}

template<typename typeK, typename typeV>
typeV &Pair<typeK, typeV>::GetValue() {
    return this->m_value;
}

#endif // PAIR_H_
