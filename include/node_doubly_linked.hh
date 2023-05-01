// Doubly linked namespace
namespace dlkd {
    template <typename typeT>
    struct Node {
        typeT _key;
        Node<typeT> *_left;
        Node<typeT> *_right;

        Node(typeT &k) : _key(k), _left(nullptr), _right(nullptr) {}
        Node(Node *left, typeT &k) : _key(k), _left(left), _right(nullptr) {}
        Node(typeT &k, Node *right) : _key(k), _left(nullptr), _right(right) {}
        Node(typeT &k, Node *left, Node *right) : _key(k), _left(left), _right(right) {}
    };
}
