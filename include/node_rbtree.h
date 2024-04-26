/*
 * Filename: node_rbtree.h
 * Created on: June 28, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef NODE_RED_BLACK_TREE_H_
#define NODE_RED_BLACK_TREE_H_

namespace rbtree
{
    enum Color
    {
        BLACK,
        RED
    };

    template<typename typeT>
    class Node
    {
        private:
            Node<typeT>* m_parent;
            Node<typeT>* m_left;
            Node<typeT>* m_right;

        protected:
            typeT m_value;
            Color m_color;

        public:
            Node(const typeT value)
                : m_parent(nullptr),
                  m_left(nullptr),
                  m_right(nullptr),
                  m_value(value),
                  m_color(RED)
            { }

            Node(const typeT value, Node<typeT>* parent)
                : m_parent(parent),
                  m_left(nullptr),
                  m_right(nullptr),
                  m_value(value),
                  m_color(RED)
            { }

            void SetColor(Color newColor);

            /**
             * @brief Sets the value of the node
             * @param newKey The new value to be assigned to the node
             */
            void SetValue(typeT newValue);

            void SetParent(Node<typeT>* node);

            /**
             * @brief Sets the left child node of the current node
             * @param lnode Pointer to the left child node to be set
             */
            void SetLeftNode(Node<typeT>* lnode);

            /**
             * @brief Sets the right child node of the current node
             * @param rnode Pointer to the right child node to be set
             */
            void SetRightNode(Node<typeT>* rnode);

            Color GetColor();

            /**
             * @brief Gets the value of the node
             * @return The key value of the node
             */
            typeT& GetValue();

            Node<typeT>* GetParent();

            /**
             * @brief Gets the left child node of the current node
             * @return Pointer to the left child node
             */
            Node<typeT>*& GetLeftNode();

            /**
             * @brief Gets the right child node of the current node
             * @return Pointer to the right child node
             */
            Node<typeT>*& GetRightNode();
    };

    template<typename typeT>
    void Node<typeT>::SetColor(Color newColor)
    {
        this->m_color = newColor;
    }

    template<typename typeT>
    void Node<typeT>::SetParent(Node<typeT>* node)
    {
        this->m_parent = node;
    }

    template<typename typeT>
    Color Node<typeT>::GetColor()
    {
        return this->m_color;
    }

    template<typename typeT>
    Node<typeT>* Node<typeT>::GetParent()
    {
        return this->m_parent;
    }

    template<typename typeT>
    void Node<typeT>::SetValue(typeT newValue)
    {
        this->m_value = newValue;
    }

    template<typename typeT>
    void Node<typeT>::SetLeftNode(Node<typeT>* lnode)
    {
        this->m_left = lnode;
    }

    template<typename typeT>
    void Node<typeT>::SetRightNode(Node<typeT>* rnode)
    {
        this->m_right = rnode;
    }

    template<typename typeT>
    typeT& Node<typeT>::GetValue()
    {
        return this->m_value;
    }

    template<typename typeT>
    Node<typeT>*& Node<typeT>::GetLeftNode()
    {
        return this->m_left;
    }

    template<typename typeT>
    Node<typeT>*& Node<typeT>::GetRightNode()
    {
        return this->m_right;
    };

} // namespace rbtree

#endif // NODE_RED_BLACK_TREE_H_
