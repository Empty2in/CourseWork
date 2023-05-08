#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include "RBTException.h"
#include "RBTNode.h"

typedef enum { BLACK, RED } Color;

template <class TreeList>
class RedBlackTree {
private:
    struct Node {
        TreeList key_;
        Node* parent_;
        Node* left_;
        Node* right_;
        Color color_;
        Node(TreeList key = TreeList(), Color color = RED, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
            key_(key),
            color_(color),
            left_(left),
            right_(right),
            parent_(p)
        {}
        Node* clone() { return new Node(*this); }
    };
    typedef Node* NodePtr;
    NodePtr root_;
    NodePtr TNULL;

    void deleteUnderTree(NodePtr tree);

    void preorder(NodePtr node);
    void inorder(NodePtr node);
    void postorder(NodePtr node);

    void leftRotate(NodePtr x);
    void rightRotate(NodePtr x);

    void transplant(NodePtr befor, NodePtr after);

    void deleteNode(NodePtr node, const TreeList& key);
    void deleteFix(NodePtr x);

    void insert(NodePtr newNode);
    void insertFix(NodePtr k);

    void print(NodePtr root, std::string indent, bool last);
    NodePtr searchNode(NodePtr node, const TreeList& key);

    RedBlackTree<TreeList>* clone();
    void copy(NodePtr cop);
    Color getNodeColor(NodePtr node) const;

public:
    RedBlackTree();
    ~RedBlackTree();
    RedBlackTree(const RedBlackTree<TreeList>& src);
    RedBlackTree(RedBlackTree<TreeList>&& src) noexcept;
    RedBlackTree<TreeList>& operator=(const RedBlackTree<TreeList>& src);
    RedBlackTree<TreeList>& operator=(RedBlackTree<TreeList>&& src) noexcept;

    bool isEmpty();
    NodePtr getRoot() const;

    void preorder();
    void inorder();
    void postorder();

    NodePtr search(const TreeList& k);
    TreeList* searchKey(const TreeList& key);

    NodePtr minimum(NodePtr node);
    NodePtr maximum(NodePtr node);
    NodePtr successor(NodePtr x);
    NodePtr predecessor(NodePtr x);

    void insert(const TreeList& key);
    void deleteNode(const TreeList& data);

    void print();
    Color getNodeColor(const TreeList& key);

    void swap(RedBlackTree<TreeList>& other);
};

template<class TreeList>
inline RedBlackTree<TreeList>::RedBlackTree() {
    try {
        TNULL = new Node;
        TNULL->color_ = BLACK;
        root_ = TNULL;
    }
    catch (std::bad_alloc& e) {
        std::cerr << "Error " << e.what();
        exit(-1);
    }
}
template<class TreeList>
inline RedBlackTree<TreeList>::~RedBlackTree() {
    deleteUnderTree(this->root_);
    delete TNULL;
}
template<class TreeList>
inline RedBlackTree<TreeList>::RedBlackTree(const RedBlackTree<TreeList>& src) {
    if (!isEmpty()) {
        this->deleteUnderTree(this->root_);
    }
    copy(src.root_);
}
template<class TreeList>
inline void RedBlackTree<TreeList>::copy(NodePtr cop) {
    if (cop != TNULL) {
        this->insert(cop);
        copy(cop->left_);
        copy(cop->right_);
    }
}

template<class TreeList>
inline Color RedBlackTree<TreeList>::getNodeColor(const TreeList& k) {
    NodePtr node = searchNode(this->root_, k);
    return getNodeColor(node);
}

template<class TreeList>
inline Color RedBlackTree<TreeList>::getNodeColor(NodePtr node) const {
    return node->color_;
}

template<class TreeList>
inline RedBlackTree<TreeList>::RedBlackTree(RedBlackTree<TreeList>&& src) noexcept {
    this->root_ = src.root_;
    this->TNULL = src.TNULL;
    src.root_ = nullptr;
    src.TNULL = nullptr;
}
template<class TreeList>
inline RedBlackTree<TreeList>& RedBlackTree<TreeList>::operator=(const RedBlackTree<TreeList>& src) {
    if (this != &src) {
        RedBlackTree<TreeList> temp(src);
        swap(temp);
    }
    return *this->clone();
}
template<class TreeList>
inline RedBlackTree<TreeList>& RedBlackTree<TreeList>::operator=(RedBlackTree<TreeList>&& src) noexcept {
    if (this != &src) {
        swap(src);
    }
    return *this;
}
template<class TreeList>
void RedBlackTree<TreeList>::deleteUnderTree(NodePtr tree) {
    if (tree && tree != TNULL) {
        deleteUnderTree(tree->left_);
        deleteUnderTree(tree->right_);
        delete tree;
    }
}
template<class TreeList>
inline void RedBlackTree<TreeList>::swap(RedBlackTree<TreeList>& other) {
    std::swap(this->root_, other->root_);
    std::swap(this->TNULL, other->TNULL);
}

template<class TreeList>
void RedBlackTree<TreeList>::preorder(NodePtr node) {
    if (node != TNULL) {
        std::cout << node->key_ << '\n';
        preorder(node->left_);
        preorder(node->right_);
    }
}
template<class TreeList>
void RedBlackTree<TreeList>::inorder(NodePtr node) {
    if (node != TNULL) {
        inorder(node->left_);
        std::cout << node->key_ << " ";
        inorder(node->right_);
    }
}
template<class TreeList>
void RedBlackTree<TreeList>::postorder(NodePtr node) {
    if (node != TNULL) {
        postorder(node->left_);
        postorder(node->right_);
        std::cout << node->key_ << " ";
    }
}
template<class TreeList>
void RedBlackTree<TreeList>::print(NodePtr root, std::string indent, bool last) {
    if (root != TNULL) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        }
        else {
            std::cout << "L----";
            indent += "|  ";
        }

        std::string sColor = root->color_ ? "RED" : "BLACK";
        std::cout << root->key_ << "(" << sColor << ")" << std::endl;
        print(root->left_, indent, false);
        print(root->right_, indent, true);
    }
}

template<class TreeList>
inline RedBlackTree<TreeList>* RedBlackTree<TreeList>::clone() {
    return new RedBlackTree<TreeList>(*this);
}

template<class TreeList>
RedBlackTree<TreeList>::template NodePtr RedBlackTree<TreeList>::search(const TreeList& k) {
    return searchNode(this->root_, k);
}
template<class TreeList>
inline TreeList* RedBlackTree<TreeList>::searchKey(const TreeList& key) {
    return &(searchNode(this->root_, key)->key_);
}
template<class TreeList>
RedBlackTree<TreeList>::template NodePtr RedBlackTree<TreeList>::searchNode(NodePtr node, const TreeList& key) {
    if (TNULL == node || node->key_ == key) {
        return node;
    }
    if (key < node->key_) {
        return searchNode(node->left_, key);
    }
    return searchNode(node->right_, key);
}
template<class TreeList>
void RedBlackTree<TreeList>::deleteFix(NodePtr x) {
    Node* s = nullptr;
    while (x != this->root_ && x->color_ == BLACK) {
        if (x == x->parent_->left_) {
            s = x->parent_->right_;
            if (s->color_ == RED) {
                s->color_ = BLACK;
                x->parent_->color_ = RED;
                leftRotate(x->parent_);
                s = x->parent_->right_;
            }

            if (s->left_->color_ == BLACK && s->right_->color_ == BLACK) {
                s->color_ = RED;
                x = x->parent_;
            }
            else {
                if (s->right_->color_ == BLACK) {
                    s->left_->color_ = BLACK;
                    s->color_ = RED;
                    rightRotate(s);
                    s = x->parent_->right_;
                }

                s->color_ = x->parent_->color_;
                x->parent_->color_ = BLACK;
                s->right_->color_ = BLACK;
                leftRotate(x->parent_);
                x = this->root_;
            }
        }
        else {
            s = x->parent_->left_;
            if (s->color_ == 1) {
                s->color_ = BLACK;
                x->parent_->color_ = RED;
                rightRotate(x->parent_);
                s = x->parent_->left_;
            }

            if (s->left_->color_ == BLACK && s->right_->color_ == BLACK) {
                s->color_ = RED;
                x = x->parent_;
            }
            else {
                if (s->left_->color_ == BLACK) {
                    s->right_->color_ = BLACK;
                    s->color_ = RED;
                    leftRotate(s);
                    s = x->parent_->left_;
                }

                s->color_ = x->parent_->color_;
                x->parent_->color_ = BLACK;
                s->left_->color_ = BLACK;
                rightRotate(x->parent_);
                x = this->root_;
            }
        }
    }
    x->color_ = BLACK;
}
template<class TreeList>
void RedBlackTree<TreeList>::deleteNode(const TreeList& data) {
    deleteNode(this->root_, data);
}
template<class TreeList>
void RedBlackTree<TreeList>::deleteNode(NodePtr node, const TreeList& key) {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
        if (node->key_ == key) {
            z = node;
        }

        if (node->key_ < key) {
            node = node->right_;
        }
        else {
            node = node->left_;
        }
    }
    if (z == TNULL) {
        return;
    }

    y = z;
    Color y_orig = y->color_;
    if (z->left_ == TNULL) {
        x = z->right_;
        transplant(z, z->right_);
    }
    else if (z->right_ == TNULL) {
        x = z->left_;
        transplant(z, z->left_);
    }
    else {
        y = minimum(z->right_);
        y_orig = y->color_;
        x = y->right_;
        if (y->parent_ == z) {
            x->parent_ = y;
        }
        else {
            transplant(y, y->right_);
            y->right_ = z->right_;
            y->right_->parent_ = y;
        }

        transplant(z, y);
        y->left_ = z->left_;
        y->left_->parent_ = y;
        y->color_ = z->color_;
    }
    delete z;
    if (y_orig == BLACK) {
        deleteFix(x);
    }
}

template<class TreeList>
void RedBlackTree<TreeList>::insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent_->color_ == RED) {
        if (k->parent_ == k->parent_->parent_->right_) {
            u = k->parent_->parent_->left_;
            if (u->color_ == RED) {
                u->color_ = BLACK;
                k->parent_->color_ = BLACK;
                k->parent_->parent_->color_ = RED;
                k = k->parent_->parent_;
            }
            else {
                if (k == k->parent_->left_) {
                    k = k->parent_;
                    rightRotate(k);
                }
                k->parent_->color_ = BLACK;
                k->parent_->parent_->color_ = RED;
                leftRotate(k->parent_->parent_);
            }
        }
        else {
            u = k->parent_->parent_->right_;

            if (u->color_ == RED) {
                u->color_ = BLACK;
                k->parent_->color_ = BLACK;
                k->parent_->parent_->color_ = RED;
                k = k->parent_->parent_;
            }
            else {
                if (k == k->parent_->right_) {
                    k = k->parent_;
                    leftRotate(k);
                }
                k->parent_->color_ = BLACK;
                k->parent_->parent_->color_ = RED;
                rightRotate(k->parent_->parent_);
            }
        }
        if (k == this->root_) {
            break;
        }
    }
    this->root_->color_ = BLACK;
}
template<class TreeList>
inline void RedBlackTree<TreeList>::insert(const TreeList& key) {
    try {
        NodePtr newNode = new Node(key);
        newNode->left_ = this->TNULL;
        newNode->right_ = this->TNULL;
        insert(newNode);
    }
    catch (std::bad_alloc& e) {
        std::cerr << "Error " << e.what();
        exit(-1);
    }
}
template<class TreeList>
void RedBlackTree<TreeList>::insert(NodePtr newNode) {
    if (newNode == nullptr) {
        throw WrongInsertKey();
    }
    NodePtr y = nullptr;
    NodePtr x = this->root_;
    while (x != TNULL) {
        y = x;
        if (newNode->key_ < x->key_) {
            x = x->left_;
        }
        else if (newNode->key_ > x->key_) {
            x = x->right_;
        }
        else {
            delete newNode;
            return;
        }
    }
    newNode->parent_ = y;
    if (y == nullptr) {
        this->root_ = newNode;
    }
    else if (newNode->key_ < y->key_) {
        y->left_ = newNode;
    }
    else {
        y->right_ = newNode;
    }
    if (newNode->parent_ == nullptr) {
        newNode->color_ = BLACK;
        return;
    }
    if (newNode->parent_->parent_ == nullptr) {
        return;
    }
    insertFix(newNode);
}

template<class TreeList>
void RedBlackTree<TreeList>::transplant(NodePtr befor, NodePtr after) {
    if (befor->parent_ == nullptr) {
        this->root_ = after;
    }
    else if (befor == befor->parent_->left_) {
        befor->parent_->left_ = after;
    }
    else {
        befor->parent_->right_ = after;
    }
    after->parent_ = befor->parent_;
}
template<class TreeList>
void RedBlackTree<TreeList>::leftRotate(NodePtr x) {
    NodePtr y = x->right_;
    x->right_ = y->left_;
    if (y->left_ != TNULL) {
        y->left_->parent_ = x;
    }
    y->parent_ = x->parent_;
    if (x->parent_ == nullptr) {
        this->root_ = y;
    }
    else if (x == x->parent_->left_) {
        x->parent_->left_ = y;
    }
    else {
        x->parent_->right_ = y;
    }
    y->left_ = x;
    x->parent_ = y;
}
template<class TreeList>
void RedBlackTree<TreeList>::rightRotate(NodePtr x) {
    NodePtr y = x->left_;
    x->left_ = y->right_;
    if (y->right_ != TNULL) {
        y->right_->parent_ = x;
    }
    y->parent_ = x->parent_;
    if (x->parent_ == nullptr) {
        this->root_ = y;
    }
    else if (x == x->parent_->right_) {
        x->parent_->right_ = y;
    }
    else {
        x->parent_->left_ = y;
    }
    y->right_ = x;
    x->parent_ = y;
}

template<class TreeList>
inline bool RedBlackTree<TreeList>::isEmpty() {
    return (this->root_ == TNULL);
}
template<class TreeList>
RedBlackTree<TreeList>::template NodePtr RedBlackTree<TreeList>::getRoot() const {
    return (this->root_);
}

template<class TreeList>
void RedBlackTree<TreeList>::print() {
    if (!isEmpty()) {
        print(this->root_, "", true);
    }
}
template<class TreeList>
void RedBlackTree<TreeList>::preorder() {
    preorder(this->root_);
}
template<class TreeList>
void RedBlackTree<TreeList>::inorder() {
    inorder(this->root_);
}
template<class TreeList>
void RedBlackTree<TreeList>::postorder() {
    postorder(this->root_);
}

template<class TreeList>
RedBlackTree<TreeList>::template NodePtr RedBlackTree<TreeList>::minimum(NodePtr node) {
    while (node->left_ != TNULL) {
        node = node->left_;
    }
    return node;
}
template<class TreeList>
RedBlackTree<TreeList>::template NodePtr RedBlackTree<TreeList>::maximum(NodePtr node) {
    while (node->right_ != TNULL) {
        node = node->right_;
    }
    return node;
}
template<class TreeList>
RedBlackTree<TreeList>::template NodePtr RedBlackTree<TreeList>::successor(NodePtr x) {
    if (x->right_ != TNULL) {
        return minimum(x->right_);
    }

    NodePtr y = x->parent_;
    while (y != TNULL && x == y->right_) {
        x = y;
        y = y->parent_;
    }
    return y;
}
template<class TreeList>
RedBlackTree<TreeList>::template NodePtr RedBlackTree<TreeList>::predecessor(NodePtr x) {
    if (x->left_ != TNULL) {
        return maximum(x->left_);
    }
    NodePtr y = x->parent_;
    while (y != TNULL && x == y->left_) {
        x = y;
        y = y->parent_;
    }
    return y;
}



#endif