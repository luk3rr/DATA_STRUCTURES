/*
* Filename: node_map.h
* Created on: June 28, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef NODE_MAP_H_
#define NODE_MAP_H_

#include "pair.h"

namespace map {
    enum Color {
        BLACK,
        RED
    };

    template<typename typeK, typename typeV>
    class Map;

    template<typename typeK, typename typeV>
    class Node {
        private:
            Pair<typeK, typeV> m_pair;
            Color m_color;
            Node<typeK, typeV> *m_left;
            Node<typeK, typeV> *m_right;
            Node<typeK, typeV> *m_parent;

        public:

            Node(const typeK& key, const typeV& value) : m_pair(key, value),
                                                        m_color(RED),
                                                        m_left(nullptr),
                                                        m_right(nullptr),
                                                        m_parent(nullptr) { }

            Node(const typeK& key, const typeV& value, Node<typeK, typeV> *parent) : m_pair(key, value),
                                                                                    m_color(RED),
                                                                                    m_left(nullptr),
                                                                                    m_right(nullptr),
                                                                                    m_parent(parent) { }

            void SetPair(const typeK &key, const typeV &value);

            void SetPair(Pair<typeK, typeV> pair);

            void SetColor(Color newColor);

            void SetLeft(Node<typeK, typeV> *node);

            void SetRight(Node<typeK, typeV> *node);

            void SetParent(Node<typeK, typeV> *node);

            Pair<typeK, typeV> &GetPair();

            Color GetColor();

            Node<typeK, typeV> *GetLeft();

            Node<typeK, typeV> *GetRight();

            Node<typeK, typeV> *GetParent();

            friend class Map<typeK, typeV>;
    };

    template<typename typeK, typename typeV>
    void Node<typeK, typeV>::SetPair(const typeK &key, const typeV &value) {
        this->m_pair.SetKey(key);
        this->m_pair.SetValue(value);
    }

    template<typename typeK, typename typeV>
    void Node<typeK, typeV>::SetPair(Pair<typeK, typeV> pair) {
        this->m_pair = pair;
    }

    template<typename typeK, typename typeV>
    void Node<typeK, typeV>::SetColor(Color newColor) {
        this->m_color = newColor;
    }

    template<typename typeK, typename typeV>
    void Node<typeK, typeV>::SetLeft(Node<typeK, typeV> *node) {
        this->m_left = node;
    }

    template<typename typeK, typename typeV>
    void Node<typeK, typeV>::SetRight(Node<typeK, typeV> *node) {
        this->m_right = node;
    }

    template<typename typeK, typename typeV>
    void Node<typeK, typeV>::SetParent(Node<typeK, typeV> *node) {
        this->m_parent = node;
    }

    template<typename typeK, typename typeV>
    Pair<typeK, typeV> &Node<typeK, typeV>::GetPair() {
        return this->m_pair;
    }

    template<typename typeK, typename typeV>
    Color Node<typeK, typeV>::GetColor() {
        return this->m_color;
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Node<typeK, typeV>::GetLeft() {
        return this->m_left;
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Node<typeK, typeV>::GetRight() {
        return this->m_right;
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Node<typeK, typeV>::GetParent() {
        return this->m_parent;
    }
}

#endif // NODE_MAP_H_
