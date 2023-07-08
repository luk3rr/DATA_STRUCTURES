/*
* Filename: node_red_black_tree.h
* Created on: June 28, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef NODE_RED_BLACK_TREE_H_
#define NODE_RED_BLACK_TREE_H_

namespace rbtree {

    template<typename typeT>
    class RedBlackTree;

    enum Color {
        BLACK,
        RED
    };

    template<typename typeT>
    class Node {
        private:
            typeT m_key;
            Color m_color;
            Node<typeT> *m_left;
            Node<typeT> *m_right;
            Node<typeT> *m_parent;

        public:

            Node(const typeT& key) : m_key(key),
                                    m_color(RED),
                                    m_left(nullptr),
                                    m_right(nullptr),
                                    m_parent(nullptr) { }

            Node(const typeT& key, Node<typeT> *parent) : m_key(key),
                                                        m_color(RED),
                                                        m_left(nullptr),
                                                        m_right(nullptr),
                                                        m_parent(parent) { }

            void SetKey(const typeT key);

            void SetColor(Color newColor);

            void SetLeft(Node<typeT> *node);

            void SetRight(Node<typeT> *node);

            void SetParent(Node<typeT> *node);

            typeT GetKey();

            Color GetColor();

            Node<typeT> *GetLeft();

            Node<typeT> *GetRight();

            Node<typeT> *GetParent();

            friend class RedBlackTree<typeT>;
    };

    template<typename typeT>
    void Node<typeT>::SetKey(const typeT key) {
        this->m_key = key;
    }

    template<typename typeT>
    void Node<typeT>::SetColor(Color newColor) {
        this->m_color = newColor;
    }

    template<typename typeT>
    void Node<typeT>::SetLeft(Node<typeT> *node) {
        this->m_left = node;
    }

    template<typename typeT>
    void Node<typeT>::SetRight(Node<typeT> *node) {
        this->m_right = node;
    }

    template<typename typeT>
    void Node<typeT>::SetParent(Node<typeT> *node) {
        this->m_parent = node;
    }

    template<typename typeT>
    typeT Node<typeT>::GetKey() {
        return this->m_key;
    }

    template<typename typeT>
    Color Node<typeT>::GetColor() {
        return this->m_color;
    }

    template<typename typeT>
    Node<typeT> *Node<typeT>::GetLeft() {
        return this->m_left;
    }

    template<typename typeT>
    Node<typeT> *Node<typeT>::GetRight() {
        return this->m_right;
    }

    template<typename typeT>
    Node<typeT> *Node<typeT>::GetParent() {
        return this->m_parent;
    }
} // rbtree namespace

#endif // NODE_RED_BLACK_TREE_H_
