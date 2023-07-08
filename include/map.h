/*
* Filename: map.h
* Created on: June 28, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <fstream>

#include "map_excpt.h"
#include "node_map.h"

namespace map {
    template<typename typeK, typename typeV>
    class Map {
        private:
            Node<typeK, typeV> *m_root;
            unsigned int m_nodes;

            /**
             * @brief Inserir um novo par no map
             * @param parent Parente do nó atual
             * @param node Nó atual da chamada recursiva
             * @param key, value Chave e valor que serão armazenados no novo nó
             * @return Ponteiro para o novo nó que foi inserido
             */
            Node<typeK, typeV> *Insert(Node<typeK, typeV> *parent, Node<typeK, typeV> *&node, const typeK &key, const typeV &value);

            /**
             * @brief Corrige as propriedades da árvore red black após uma inserção
             * @param Nó que foi inserido
             **/
            void FixInsert(Node<typeK, typeV> *node);

            /**
             * @brief Deleta um determinado nó
             * @param node Nó que será deletado
             */
            void DeleteNode(Node<typeK, typeV> *node);

            /**
             * @brief Corrige as propriedades da árvore red black após uma remoção
             * @param Nó que se iniciará a correção
             **/
            void FixDelete(Node<typeK, typeV> *node);

            /**
             * @brief Faz o transplante entre dois nós
             * @param node1, node2 Nós que serão transplantados
             **/
            void Transplant(Node<typeK, typeV> *&node1, Node<typeK, typeV> *&node2);

            /**
             * @brief Busca pelo nó que contém uma determinada chave
             * @param key Chave que será usada na busca
             * @return Ponteiro para o nó ou nullptr caso o nó não tenha sido encontrado
             **/
            Node<typeK, typeV> *Search(const typeK &key);

            /**
             * @brief Busca pelo nó que contém uma determinada chave
             * @param node Nó atual da chamada recursiva
             * @param key Chave que será usada na busca
             * @return Ponteiro para o nó ou nullptr caso o nó não tenha sido encontrado
             **/
            Node<typeK, typeV> *Search(Node<typeK, typeV> *node, const typeK &key);

            /**
             * @brief Realiza a rotação para a esquerda
             * @param node Nó que será rotacionado
             * @return Ponteiro para o nó que que ficou no lugar do nó que foi rotacionado
             **/
            Node<typeK, typeV> *RotateLeft(Node<typeK, typeV> *node);

            /**
             * @brief Realiza a rotação para a direita
             * @param node Nó que será rotacionado
             * @return Ponteiro para o nó que que ficou no lugar do nó que foi rotacionado
             **/
            Node<typeK, typeV> *RotateRight(Node<typeK, typeV> *node);

            /**
             * @brief Move um nó vermelho para a esquerda
             * @param node Nó que será movido
             * @return Ponteiro para o nó que que ficou no lugar do nó que foi movido
             **/
            Node<typeK, typeV> *MoveRed2Left(Node<typeK, typeV> *node);

            /**
             * @brief Move um nó vermelho para a direita
             * @param node Nó que será movido
             * @return Ponteiro para o nó que que ficou no lugar do nó que foi movido
             **/
            Node<typeK, typeV> *MoveRed2Right(Node<typeK, typeV> *node);

            /**
             * @brief Busca o nó mais a esquerda (menor chave)
             * @param node Nó onde a busca será iniciada
             * @return Ponteiro para o nó mais a esquerda
             **/
            Node<typeK, typeV> *FindLeftMostNode(Node<typeK, typeV> *node);

            /**
             * @brief Deleta o nó mais a esquerda
             * @param node Nó onde será iniciada a busca do nó mais a esquerda
             * @return
             **/
            Node<typeK, typeV> *DeleteLeftMostNode(Node<typeK, typeV> *node);

            /**
             * @brief Modifica a cor de uma família de nós (nó e seus filhos)
             * @param parent Nó onde ocorrerá a modificação
             **/
            void ChangeFamilyColor(Node<typeK, typeV> *parent);

            /**
             * @brief Deleta todo o map (chamada recursiva)
             */
            void Clear(Node<typeK, typeV> *&node);

            /**
            @brief Imprime a árvore
            @param output Arquivo em que a impressão será feita
            @param node Nó atual
            @param side, deve receber True se o nó está o lado esquerdo ou False, caso o nó esteja do lado direito
            */
            void DumpTree(Node<typeK, typeV> *&node, const std::string &vBar, std::ofstream &output, bool sideIsLeft);

            /**
             * @brief Verifica a quantidade de nós pretos na árvore
             * @param node Nó atual da chamada recursiva
             * @return A quantidade de nós pretos
             **/
            int GetBlackNodeCount(Node<typeK, typeV> *&node);

            /**
             * @brief Verifica se as propriedades da red black tree estão satisfeitas
             * @param node Nó atual da chamada recursiva
             **/
            bool IsRedBlackTreeBalanced(Node<typeK, typeV> *&node);

        public:
            Map();

            ~Map();

            /**
             * @brief Overload do operador []
             * @param key Chave que será buscada
             * @return O valor da chave correspondente
             **/
            typeV &operator[](const typeK &key);

            /**
             * @brief Overload para inserir um novo elemento sem o apontador para o nó
             * @param key, value Chave e valor que serão inseridos
             * @return Ponteiro para o nó que foi inserido
             */
            Node<typeK, typeV> *Insert(const typeK &key, const typeV &value);

            /**
             * @brief Diz a quantidade de elementos que há no map
             * @return Quantidade de elementos no map
             */
            unsigned int Size();

            /**
             * @brief Diz se o map está vazio
             * @return True se estiver vazio, False caso contrário
             **/
            bool IsEmpty();

            /**
             * @brief Diz se a árvore está balanceada
             * @return True se estiver, False caso contrário
             **/
            bool IsRedBlackTreeBalanced();

            /**
             * @brief Diz se uma chave está no map
             * @return True se estiver, False caso contrário
             **/
            bool Contains(const typeK &key);

            /**
             * @brief Imprime a árvore
             * @param output Arquivo em que a impressão será feita
             **/
            void DumpTree(std::ofstream &output);

            /**
             * @brief Remove um elemento do map
             * @param key Chave do elemento que será removido
             **/
            void Remove(const typeK &key);

            /**
             * @brief Deleta todo o map
             */
            void Clear();

            // Implementação do iterator
            using pointer = Node<typeK, typeV> *;
            using reference = Node<typeK, typeV> &;

            typedef struct Iterator {
                private:
                    pointer m_ptr;

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
                        if (m_ptr == nullptr)
                            return *this;

                        if (m_ptr->GetRight() != nullptr) {
                            m_ptr = m_ptr->GetRight();

                            while (m_ptr->GetLeft() != nullptr)
                                m_ptr = m_ptr->GetLeft();

                        }
                        else {
                            while (true) {
                                if (m_ptr->GetParent() == nullptr) {
                                    m_ptr = nullptr;
                                    break;
                                }

                                if (m_ptr == m_ptr->GetParent()->GetLeft()) {
                                    m_ptr = m_ptr->GetParent();
                                    break;
                                }

                                m_ptr = m_ptr->GetParent();
                            }
                        }

                        return *this;                    }

                    Iterator operator++(int) {
                        Iterator tmp = *this;
                        ++(*this);
                        return tmp;
                    }

                    bool operator==(const Iterator& other) const {
                        return m_ptr == other.m_ptr;
                    }

                    bool operator!=(const Iterator& other) const {
                        return !(*this == other);
                    }

                    Pair<typeK, typeV>& operator*() {
                        return m_ptr->GetPair();
                    }

            } Iterator;

        Iterator begin() {
            Node<typeK, typeV> *leftMost = this->m_root;

            while (leftMost != nullptr and leftMost->GetLeft() != nullptr) {
                leftMost = leftMost->GetLeft();
            }
            return Iterator(leftMost);
        }

        Iterator end() {
            return Iterator(nullptr);
        }

    };

    template<typename typeK, typename typeV>
    Map<typeK, typeV>::Map() {
        this->m_root = nullptr;
        this->m_nodes = 0;
    }

    template<typename typeK, typename typeV>
    Map<typeK, typeV>::~Map() {
        this->Clear();
    }

    template<typename typeK, typename typeV>
    typeV &Map<typeK, typeV>::operator[](const typeK& key) {
        Node<typeK, typeV>* node = this->Search(key);

        if (node != nullptr)
            return node->GetPair().GetValue();

        return this->Insert(key, typeV())->GetPair().GetValue();
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::Insert(const typeK &key, const typeV &value) {
        if (this->m_root == nullptr) {
            this->m_root = new Node<typeK, typeV>(key, value);
            this->m_nodes++;
            this->m_root->SetColor(BLACK);
            return this->m_root;
        }
        else {
            if (key < this->m_root->GetPair().GetKey())
                return this->Insert(this->m_root, this->m_root->m_left, key, value);

            else
                return this->Insert(this->m_root, this->m_root->m_right, key, value);
        }
    }

    template <typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::Insert(Node<typeK, typeV> *parent, Node<typeK, typeV> *&node, const typeK &key, const typeV &value) {
        if (node == nullptr) {
            node = new Node<typeK, typeV>(key, value, parent);
            this->m_nodes++;
            this->FixInsert(node);
            return node;
        }
        else {
            if (key < node->GetPair().GetKey())
                return this->Insert(node, node->m_left, key, value);

            else
                return this->Insert(node, node->m_right, key, value);
        }
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::FixInsert(Node<typeK, typeV> *node) {
         Node<typeK, typeV> *uncle = nullptr;

        while (node != this->m_root and node->GetParent() and node->GetParent()->GetColor() == RED) {
            if (node->GetParent() == node->GetParent()->GetParent()->GetRight()) {

                uncle = node->GetParent()->GetParent()->GetLeft();

                if (uncle and uncle->GetColor() == RED) {
                    uncle->SetColor(BLACK);
                    node->GetParent()->SetColor(BLACK);
                    node->GetParent()->GetParent()->SetColor(RED);
                    node = node->GetParent()->GetParent();
                }
                else {
                    if (node == node->GetParent()->GetLeft()) {
                        node = node->GetParent();
                        this->RotateRight(node);
                    }
                    node->GetParent()->SetColor(BLACK);
                    node->GetParent()->GetParent()->SetColor(RED);
                    this->RotateLeft(node->GetParent()->GetParent());
                }
            }
            else {
                uncle = node->GetParent()->GetParent()->GetRight();

                if (uncle and uncle->GetColor() == RED) {
                    uncle->SetColor(BLACK);
                    node->GetParent()->SetColor(BLACK);
                    node->GetParent()->GetParent()->SetColor(RED);
                    node = node->GetParent()->GetParent();
                }
                else {
                    if (node == node->GetParent()->GetRight()) {
                        node = node->GetParent();
                        this->RotateLeft(node);
                    }
                    node->GetParent()->SetColor(BLACK);
                    node->GetParent()->GetParent()->SetColor(RED);
                    this->RotateRight(node->GetParent()->GetParent());
                }
            }
        }
        this->m_root->SetColor(BLACK);
    }

    template<typename typeK, typename typeV>
    unsigned int Map<typeK, typeV>::Size() {
        return this->m_nodes;
    }

    template<typename typeK, typename typeV>
    bool Map<typeK, typeV>::IsEmpty() {
        if (this->m_nodes == 0)
            return true;

        return false;
    }

    template<typename typeK, typename typeV>
    bool Map<typeK, typeV>::Contains(const typeK &key) {
        if (this->Search(key) == nullptr)
            return false;

        return true;
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::Remove(const typeK &key) {
        this->DeleteNode(this->Search(key));
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::DeleteNode(Node<typeK, typeV> *node) {
        if (node == nullptr)
            return;

        Node<typeK, typeV> *nodeCopy = node;
        Node<typeK, typeV> *aux;
        Color nodeColor = node->GetColor();

        if (node->m_left == nullptr) {
            aux = node->GetRight();
            this->Transplant(node, node->m_right);
        }
        else if (node->GetRight() == nullptr) {
            aux = node->GetLeft();
            this->Transplant(node, node->m_left);
        }
        else {
            nodeCopy = this->FindLeftMostNode(node->GetRight());
            nodeColor = nodeCopy->GetColor();
            aux = nodeCopy->GetRight();

            if (aux and nodeCopy->GetParent() == node) {
                aux->SetParent(nodeCopy);
            }
            else {
                this->Transplant(nodeCopy, nodeCopy->m_right);
                nodeCopy->SetRight(node->GetRight());

                if (nodeCopy->GetRight() and nodeCopy->GetRight()->GetParent())
                    nodeCopy->GetRight()->SetParent(nodeCopy);
            }

            this->Transplant(node, nodeCopy);

            nodeCopy->SetLeft(node->GetLeft());
            nodeCopy->GetLeft()->SetParent(nodeCopy);
            nodeCopy->SetColor(node->GetColor());
        }
        delete node;
        this->m_nodes--;

        if (nodeColor == BLACK) {
            this->FixDelete(aux);
        }
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::FixDelete(Node<typeK, typeV> *node) {
        Node<typeK, typeV> *aux = nullptr;

        while (node != this->m_root and node and node->GetColor() == BLACK) {
            if (node == node->GetParent()->GetLeft()) {
                aux = node->GetParent()->GetRight();

                if (aux and aux->GetColor() == RED) {
                    aux->SetColor(BLACK);
                    node->GetParent()->SetColor(RED);
                    this->RotateLeft(node->GetParent());
                    aux = node->GetParent()->GetRight();
                }

                if (aux->GetLeft() and aux->GetLeft()->GetColor() == BLACK and aux->GetRight() and aux->GetRight()->GetColor() == BLACK) {
                    aux->SetColor(RED);
                    node = node->GetParent();
                }
                else {
                    if (aux->GetRight() and aux->GetRight()->GetColor() == BLACK) {
                        aux->GetLeft()->SetColor(BLACK);
                        aux->SetColor(RED);
                        this->RotateRight(aux);
                        aux = node->GetParent()->GetRight();
                    }

                    aux->SetColor(node->GetParent()->GetColor());
                    node->GetParent()->SetColor(BLACK);
                    aux->GetRight()->SetColor(BLACK);
                    this->RotateLeft(node->GetParent());
                    node = this->m_root;
                }
            }
            else {
                aux = node->GetParent()->GetLeft();
                if (aux and aux->GetColor() == RED) {
                    aux->SetColor(BLACK);
                    node->GetParent()->SetColor(RED);
                    this->RotateRight(node->GetParent());
                    aux = node->GetParent()->GetLeft();
                }

                // Possivel erro nesse if
                if (aux->GetRight() and aux->GetRight()->GetColor() == BLACK) {
                    aux->SetColor(RED);
                    node = node->GetParent();
                }
                else {
                    if (aux->GetLeft() and aux->GetLeft()->GetColor() == BLACK) {
                        aux->GetRight()->SetColor(BLACK);
                        aux->SetColor(RED);
                        this->RotateLeft(aux);
                        aux = node->GetParent()->GetLeft();
                    }
                }

                aux->SetColor(node->GetParent()->GetColor());
                node->GetParent()->SetColor(BLACK);
                aux->GetLeft()->SetColor(BLACK);
                this->RotateRight(node->GetParent());
                node = this->m_root;
            }
        }
        if (node != nullptr)
            node->SetColor(BLACK);
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::Transplant(Node<typeK, typeV> *&node1, Node<typeK, typeV> *&node2) {
        if (node1->GetParent() == nullptr)
            this->m_root = node2;

        else if (node1 == node1->GetParent()->GetLeft())
            node1->GetParent()->SetLeft(node2);

        else
            node1->GetParent()->SetRight(node2);

        if (node2 != nullptr)
            node2->SetParent(node1->GetParent());
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::Search(const typeK &key) {
        return this->Search(this->m_root, key);
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::Search(Node<typeK, typeV> *node, const typeK &key) {
        if (node == nullptr or key == node->GetPair().GetKey())
            return node;

        if (key < node->GetPair().GetKey())
            return this->Search(node->m_left, key);

        else
            return this->Search(node->m_right, key);
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::RotateLeft(Node<typeK, typeV> *node) {
        if (node == nullptr or node->GetRight() == nullptr)
            return node;

        Node<typeK, typeV> *pivot = node->GetRight();
        node->SetRight(pivot->GetLeft());

        if (pivot->GetLeft() != nullptr)
            pivot->GetLeft()->SetParent(node);

        pivot->SetParent(node->GetParent());

        if (node->GetParent() == nullptr)
            this->m_root = pivot;

        else if (node == node->GetParent()->GetLeft())
            node->GetParent()->SetLeft(pivot);

        else
            node->GetParent()->SetRight(pivot);

        pivot->SetLeft(node);
        node->SetParent(pivot);

        return pivot;
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::RotateRight(Node<typeK, typeV> *node) {
        if (node == nullptr or node->GetLeft() == nullptr)
            return node;

        Node<typeK, typeV> *pivot = node->GetLeft();
        node->SetLeft(pivot->GetRight());

        if (pivot->GetRight() != nullptr)
            pivot->GetRight()->SetParent(node);

        pivot->SetParent(node->GetParent());

        if (node->GetParent() == nullptr)
            this->m_root = pivot;

        else if (node == node->GetParent()->GetLeft())
            node->GetParent()->SetLeft(pivot);

        else
            node->GetParent()->SetRight(pivot);

        pivot->SetRight(node);
        node->SetParent(pivot);

        return pivot;
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::MoveRed2Left(Node<typeK, typeV> *node) {
        this->ChangeFamilyColor(node);

        if (node->GetRight() != nullptr and node->GetRight()->GetLeft() != nullptr and node->GetRight()->GetLeft()->GetColor() == RED) {
            node->SetRight(this->RotateRight(node->GetRight()));
            node = this->RotateLeft(node);
            this->ChangeFamilyColor(node);
        }

        return node;
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::MoveRed2Right(Node<typeK, typeV> *node) {
        this->ChangeFamilyColor(node);

        if (node->GetLeft() != nullptr and node->GetLeft()->GetLeft() != nullptr and node->GetLeft()->GetLeft()->GetColor() == RED) {
            node = this->RotateRight(node);
            this->ChangeFamilyColor(node);
        }

        return node;
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::ChangeFamilyColor(Node<typeK, typeV> *parent) {
        parent->SetColor(parent->GetColor() == BLACK ? RED : BLACK);

        if (parent->GetLeft() != nullptr)
            parent->GetLeft()->SetColor(parent->GetLeft()->GetColor() == BLACK ? RED : BLACK);

        if (parent->GetRight() != nullptr)
            parent->GetRight()->SetColor(parent->GetRight()->GetColor() == BLACK ? RED : BLACK);
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::FindLeftMostNode(Node<typeK, typeV> *node) {
        Node<typeK, typeV> *current = node;

        while (current and current->m_left != nullptr) {
            current = current->m_left;
        }

        return current;
    }

    template<typename typeK, typename typeV>
    Node<typeK, typeV> *Map<typeK, typeV>::DeleteLeftMostNode(Node<typeK, typeV> *node) {
        if (node == nullptr)
            return nullptr;

        if (node->GetLeft() == nullptr) {
            Node<typeK, typeV>* rightChild = node->GetRight();
            delete node;
            this->m_nodes--;
            return rightChild;
        }

        if (node->GetLeft() and node->GetLeft()->GetColor() == BLACK and node->GetLeft()->GetLeft() and node->GetLeft()->GetLeft()->GetColor() == BLACK) {
            node = this->MoveRed2Left(node);
        }

        node->SetLeft(DeleteLeftMostNode(node->GetLeft()));
        this->FixDelete(node);
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::Clear() {
        this->Clear(this->m_root);
        this->m_root = nullptr;
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::Clear(Node<typeK, typeV> *&node) {
        if (node != nullptr) {
            this->Clear(node->m_left);
            this->Clear(node->m_right);
            delete node;
            this->m_nodes--;
        }
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::DumpTree(std::ofstream &output) {
        if (this->m_root != nullptr) {
            output << this->m_root->GetPair().GetKey()
                   << ":" << this->m_root->m_color
                   << std::endl;
            this->DumpTree(this->m_root->m_left, "", output, true);
            this->DumpTree(this->m_root->m_right, "", output, false);
        }
    }

    template<typename typeK, typename typeV>
    void Map<typeK, typeV>::DumpTree(Node<typeK, typeV> *&node, const std::string &vBar, std::ofstream &output, bool sideIsLeft) {
        if (node != nullptr) {
            if (sideIsLeft) {
                output << vBar << "├───" << node->GetPair().GetKey() << ":" << node->GetColor() << std::endl;
            }
            else {
                output << vBar << "└───" << node->GetPair().GetKey() << ":" << node->GetColor() << std::endl;
            }
            this->DumpTree(node->m_left, vBar + (sideIsLeft ? "│    " : "     "), output, true);
            this->DumpTree(node->m_right, vBar + (sideIsLeft ? "│    " : "     "), output, false);
        }
    }

    template<typename typeK, typename typeV>
    bool Map<typeK, typeV>::IsRedBlackTreeBalanced(Node<typeK, typeV> *&node) {
        if (node == nullptr)
            return true;

        // Verifica a propriedade das cores
        if (node->GetColor() != RED and node->GetColor() != BLACK)
            return false;

        // Verifica a propriedade da raiz
        if (node == m_root and node->GetColor() != BLACK)
            return false;

        // Verifica a propriedade dos filhos vermelhos
        if (node->GetColor() == RED) {
            if (node->GetLeft() and node->GetLeft()->GetColor() != BLACK)
                return false;

            if (node->GetRight() and node->GetRight()->GetColor() != BLACK)
                return false;
        }

        // Verifica a propriedade dos caminhos pretos
        int leftBlackCount = GetBlackNodeCount(node->m_left);
        int rightBlackCount = GetBlackNodeCount(node->m_right);
        if (leftBlackCount != rightBlackCount)
            return false;

        return IsRedBlackTreeBalanced(node->m_left) and IsRedBlackTreeBalanced(node->m_right);
    }

    template<typename typeK, typename typeV>
    int Map<typeK, typeV>::GetBlackNodeCount(Node<typeK, typeV> *&node) {
        if (node == nullptr)
            return 1;  // Folhas nulas são consideradas pretas

        int leftCount = GetBlackNodeCount(node->m_left);
        int rightCount = GetBlackNodeCount(node->m_right);

        // Incrementa o contador apenas para nós pretos
        return node->GetColor() == BLACK ? leftCount + 1 : rightCount;
    }

    template<typename typeK, typename typeV>
    bool Map<typeK, typeV>::IsRedBlackTreeBalanced() {
        return this->IsRedBlackTreeBalanced(this->m_root);
    }
}

#endif // MAP_H_
