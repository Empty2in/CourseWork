#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include "RBTException.h"
#include "RBTNode.h"

typedef enum { BLACK, RED } Color;

template < class TreeList >
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
    void transplant(NodePtr befor, NodePtr after);

    void preorder(NodePtr node, std::ostream& out) const;
    void inorder(NodePtr node, std::ostream& out) const;
    void postorder(NodePtr node, std::ostream& out) const;

    void leftRotate(NodePtr x);
    void rightRotate(NodePtr x);

    void deleteNode(NodePtr node, const TreeList& key);
    void deleteFix(NodePtr x);

    void insert(NodePtr newNode);
    void insertFix(NodePtr k);

    void print(std::ostream& out, NodePtr root, std::string indent, bool last) const;
    NodePtr searchNode(NodePtr node, const TreeList& key);

    void copy(NodePtr cop, NodePtr tnull);

public:
    RedBlackTree();
    ~RedBlackTree();
    RedBlackTree(const RedBlackTree< TreeList >& src);
    RedBlackTree(RedBlackTree< TreeList >&& src) noexcept;
    RedBlackTree<TreeList>& operator=(const RedBlackTree<TreeList>& src);
    RedBlackTree<TreeList>& operator=(RedBlackTree<TreeList>&& src) noexcept;

    bool isEmpty() const;
    NodePtr getRoot() const;

    void print(std::ostream& out) const;
    void preorder(std::ostream& out) const;
    void inorder(std::ostream& out) const;
    void postorder(std::ostream& out) const;

    bool search(const TreeList& k);
    TreeList* searchKey(const TreeList& key);

    NodePtr minimum(NodePtr node);
    NodePtr maximum(NodePtr node);

    void insert(const TreeList& key);
    void deleteNode(const TreeList& data);

    void clear();
    Color getNodeColor(const TreeList& key);

    void swap(RedBlackTree<TreeList>& other);
    RedBlackTree<TreeList>* clone();
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
    this->clear();
    delete TNULL;
}
template<class TreeList>
inline RedBlackTree<TreeList>::RedBlackTree(const RedBlackTree<TreeList>& src) {
    this->TNULL = src.TNULL->clone();
    this->TNULL->color_ = BLACK;
    this->root_ = TNULL;
    this->copy(src.root_, src.TNULL);
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
    return *this;
}
template<class TreeList>
inline RedBlackTree<TreeList>& RedBlackTree<TreeList>::operator=(RedBlackTree<TreeList>&& src) noexcept {
    if (this != &src) {
        swap(src);
    }
    return *this;
}

template<class TreeList>
void RedBlackTree<TreeList>::preorder(NodePtr node, std::ostream& out) const {
    if (node != TNULL) {
        std::cout << node->key_ << '\n';
        preorder(node->left_, out);
        preorder(node->right_, out);
    }
}
template<class TreeList>
void RedBlackTree<TreeList>::inorder(NodePtr node, std::ostream& out) const {
    if (node != TNULL) {
        inorder(node->left_, out);
        out << node->key_ << '\n';
        inorder(node->right_, out);
    }
}
template<class TreeList>
void RedBlackTree<TreeList>::postorder(NodePtr node, std::ostream& out) const {
    if (node != TNULL) {
        postorder(node->left_, out);
        postorder(node->right_, out);
        std::cout << node->key_ << '\n';
    }
}
template<class TreeList>
void RedBlackTree<TreeList>::print(std::ostream& out, NodePtr root, std::string indent, bool last) const {
    if (root != TNULL) {
        out << indent;
        if (last) {
            out << "R----";
            indent += "   ";
        }
        else {
            out << "L----";
            indent += "|  ";
        }

        std::string sColor = root->color_ ? "RED" : "BLACK";
        out << "(" << sColor << ") " << root->key_ << '\n';
        print(out, root->left_, indent, false);
        print(out, root->right_, indent, true);
    }
}

template<class TreeList>
inline RedBlackTree<TreeList>* RedBlackTree<TreeList>::clone() {
    return (new RedBlackTree<TreeList>(*this));
}

template<class TreeList>
bool RedBlackTree<TreeList>::search(const TreeList& k) {
    NodePtr serchNode = searchNode(this->root_, k);
    if (serchNode != nullptr && serchNode != TNULL) {
        return true;
    }
    return false;
}
template<class TreeList>
inline TreeList* RedBlackTree<TreeList>::searchKey(const TreeList& key) {
    NodePtr node = searchNode(this->root_, key);
    if (node == TNULL) {
        return nullptr;
    }
    return &node->key_;
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
void RedBlackTree<TreeList>::deleteNode(const TreeList& data) {
    deleteNode(this->root_, data);
}
template<class TreeList>
void RedBlackTree<TreeList>::deleteNode(NodePtr node, const TreeList& key) {
    NodePtr z = searchNode(this->root_, key);
    if (z == nullptr || z == TNULL) {
        return;
    }
    NodePtr x, y;
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
void RedBlackTree<TreeList>::deleteFix(NodePtr x) {
    NodePtr s = nullptr;
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
            if (s->color_ == RED) {
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
RedBlackTree<TreeList>::template NodePtr RedBlackTree<TreeList>::getRoot() const {
    return (this->root_);
}
template<class TreeList>
inline Color RedBlackTree<TreeList>::getNodeColor(const TreeList& k) {
    NodePtr node = searchNode(this->root_, k);
    return node->color_;
}

template<class TreeList>
inline bool RedBlackTree<TreeList>::isEmpty() const {
    return (this->root_ == TNULL);
}
template<class TreeList>
inline void RedBlackTree<TreeList>::copy(NodePtr cop, NodePtr tnull) {
    if (cop != tnull) {
        this->insert(cop->key_);
        copy(cop->left_, tnull);
        copy(cop->right_, tnull);
    }
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
    std::swap(this->root_, other.root_);
    std::swap(this->TNULL, other.TNULL);
}
template<class TreeList>
inline void RedBlackTree<TreeList>::clear() {
    deleteUnderTree(this->root_);
}

template<class TreeList>
void RedBlackTree<TreeList>::print(std::ostream& out) const {
    if (!isEmpty()) {
        print(out, this->root_, "", true);
    }
}
template<class TreeList>
void RedBlackTree<TreeList>::preorder(std::ostream& out) const {
    preorder(this->root_, out);
}
template<class TreeList>
void RedBlackTree<TreeList>::inorder(std::ostream& out) const {
    inorder(this->root_, out);
}
template<class TreeList>
void RedBlackTree<TreeList>::postorder(std::ostream& out) const {
    postorder(this->root_, out);
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

#endif