#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>
#include "DoubleListException.h"

template <class DoubleNode>
class DoubleList {
private:
	class Node {
	public:
		Node* prev_;
		Node* next_;
		DoubleNode key_;
		Node(DoubleNode key = DoubleNode(), Node* prev = nullptr, Node* next = nullptr) :
			key_(key),
			prev_(prev),
			next_(next)
		{}
		Node* clone() { return new Node(*this); }
	};
	typedef Node* NodePtr;
	NodePtr head_;
	NodePtr tail_;
	size_t size_;

	void deleteTailNode();
	void deleteHeadNode();
	void deleteNode(NodePtr delNode);

	void insertNode(NodePtr newNode);
	void insertHead(NodePtr newNode);
	void insertTail(NodePtr newNode);
	void insertEmpty(NodePtr newNode);

	NodePtr searchNode(const DoubleNode& key);

	void printList(std::ostream& out) const;

	friend std::ostream& operator<<(std::ostream& out, const DoubleList<std::string>& node);

public:
	DoubleList();
	~DoubleList();

	DoubleList(const DoubleList<DoubleNode>& other);
	DoubleList(DoubleList<DoubleNode>&& other) noexcept;
	DoubleList<DoubleNode>& operator=(const DoubleList<DoubleNode>& other);
	inline DoubleList<DoubleNode>& operator=(DoubleList<DoubleNode>&& other) noexcept;

	DoubleNode front() const;
	DoubleNode back() const;
	size_t size() const;

	void print(std::ostream& out) const;
	bool isEmpty() const;
	void clear();
	void swap(DoubleList<DoubleNode>& other) noexcept;
	DoubleList<DoubleNode>* clone();

	void insert(const DoubleNode& key);

	void deleteTail();
	void deleteHead();
	void deleteKey(const DoubleNode& key);

	bool searchKey(const DoubleNode& key);

	void merge(DoubleList<DoubleNode>& other);
};

template<class DoubleNode>
inline DoubleList<DoubleNode>::DoubleList() :
	head_(nullptr),
	tail_(nullptr),
	size_(0)
{};
template<class DoubleNode>
inline DoubleList<DoubleNode>::~DoubleList() {
	this->clear();
}
template<class DoubleNode>
inline DoubleList<DoubleNode>::DoubleList(const DoubleList<DoubleNode>& other) {
	if (!isEmpty()) {
		this->clear();
	}
	NodePtr temp = other.head_;
	while (temp != nullptr) {
		this->insertNode(temp->clone());
		temp = temp->next_;
	}
}
template<class DoubleNode>
inline DoubleList<DoubleNode>::DoubleList(DoubleList<DoubleNode>&& other) noexcept {
	this->head_ = other.head_;
	this->tail_ = other.tail_;
	this->size_ = other.size_;
	other.head_ = nullptr;
	other.tail_ = nullptr;
	other.size_ = 0;
}

template<class DoubleNode>
inline DoubleList<DoubleNode>& DoubleList<DoubleNode>::operator=(const DoubleList<DoubleNode>& other) {
	if (this != &other) {
		this->clear();
		DoubleList<DoubleNode> temp(other);
		swap(temp);
	}
	return *this->clone();

}
template<class DoubleNode>
inline DoubleList<DoubleNode>& DoubleList<DoubleNode>::operator=(DoubleList<DoubleNode>&& other) noexcept {
	if (this != &other) {
		swap(other);
	}
	return *this;
}

template<class DoubleNode>
inline DoubleNode DoubleList<DoubleNode>::front() const {
	return this->head_->key_;
}
template<class DoubleNode>
inline DoubleNode DoubleList<DoubleNode>::back() const {
	return this->tail_->key_;
}
template<class DoubleNode>
inline size_t DoubleList<DoubleNode>::size() const {
	return this->size_;
}
template<class DoubleNode>

inline void DoubleList<DoubleNode>::print(std::ostream& out) const {
	this->printList(out);
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::printList(std::ostream& out) const{
	if (isEmpty()) {
		return;
	}
	else {
		NodePtr temp = this->head_;
		while (temp != nullptr) {
			out << temp->key_ << "; ";
			temp = temp->next_;
		}
	}
}

template<class DoubleNode>
inline void DoubleList<DoubleNode>::insert(const DoubleNode& key) {
	try {
		NodePtr newNode = new Node(key);
		insertNode(newNode);
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::insertNode(NodePtr newNode) {
	if (newNode == nullptr) {
		throw WrongInsertKeyDL();
	}
	if (isEmpty()) {
		insertEmpty(newNode);
		return;
	}
	else if (newNode->key_ < this->head_->key_) {
		insertHead(newNode);
	}
	else if (newNode->key_ > this->tail_->key_) {
		insertTail(newNode);
	}
	else {
		NodePtr temp = this->head_;
		while (temp->key_ < newNode->key_) {
			temp = temp->next_;
		}
		if (temp->key_ != newNode->key_) {
			temp->prev_->next_ = newNode;
			newNode->prev_ = temp->prev_;
			temp->prev_ = newNode;
			newNode->next_ = temp;
			this->size_++;
		}
		else {
			delete newNode;
			return;
		}
	}
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::insertHead(NodePtr newNode) {
	if (newNode == nullptr) {
		throw WrongInsertKeyDL();
	}
	if (isEmpty()) {
		insertEmpty(newNode);
	}
	else {
		newNode->next_ = this->head_;
		this->head_->prev_ = newNode;
		this->head_ = newNode;
		this->size_++;
	}
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::insertTail(NodePtr newNode) {
	if (newNode == nullptr) {
		throw WrongInsertKeyDL();
	}
	if (isEmpty()) {
		insertEmpty(newNode);
	}
	else {
		this->tail_->next_ = newNode;
		newNode->prev_ = this->tail_;
		this->tail_ = newNode;
		this->size_++;
	}
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::insertEmpty(NodePtr newNode) {
	this->head_ = newNode;
	this->tail_ = newNode;
	this->size_++;
}

template<class DoubleNode>
inline void DoubleList<DoubleNode>::deleteKey(const DoubleNode& key) {
	NodePtr delNode = searchNode(key);
	if (delNode) {
		deleteNode(delNode);
	}
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::deleteTail() {
	deleteTailNode();
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::deleteHead() {
	deleteHeadNode();
}

template<class DoubleNode>
inline void DoubleList<DoubleNode>::deleteNode(NodePtr delNode) {
	if (delNode == nullptr) {
		throw WrongDeleteKeyDL();;
	}
	if (isEmpty()) {
		throw DeleteFromEmptyDL();
	}
	else {
		if (delNode == this->head_) {
			deleteHead();
		}
		else if (delNode == this->tail_) {
			deleteTail();
		}
		else {
			delNode->prev_->next_ = delNode->next_;
			delNode->next_->prev_ = delNode->prev_;
			this->size_--;
			delete delNode;
		}
	}
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::deleteTailNode() {
	if (isEmpty()) {
		throw DeleteFromEmptyDL();
	}
	else if (tail_ == nullptr) {
		throw DeleteEmptyTailDL();
	}
	else {
		NodePtr temp = this->tail_;
		if (temp->prev_ != nullptr) {
			temp->prev_->next_ = nullptr;
			this->tail_ = temp->prev_;
		}
		else {
			head_ = nullptr;
			tail_ = nullptr;
		}
		this->size_--;
		delete temp;
	}
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::deleteHeadNode() {
	if (isEmpty()) {
		throw DeleteFromEmptyDL();
	}
	else if (head_ == nullptr) {
		throw DeleteEmptyHeadDL();
	}
	else {
		NodePtr temp = this->head_;
		if (temp->next_ != nullptr) {
			temp->next_->prev_ = nullptr;
			this->head_ = temp->next_;
		}
		else {
			head_ = nullptr;
			tail_ = nullptr;
		}
		this->size_--;
		delete temp;
	}
}

template<class DoubleNode>
inline bool DoubleList<DoubleNode>::searchKey(const DoubleNode& key) {
	return this->searchNode(key);
}
template<class DoubleNode>
inline DoubleList<DoubleNode>::template NodePtr DoubleList<DoubleNode>::searchNode(const DoubleNode& key) {
	if (isEmpty()) {
		return nullptr;
	}
	NodePtr temp = this->tail_;
	if (key == temp->key_) {
		return temp;
	}
	temp = this->head_;
	while (temp != nullptr && temp->key_ != key) {
		temp = temp->next_;
	}
	return temp;
}


template<class DoubleNode>
inline void DoubleList<DoubleNode>::merge(DoubleList<DoubleNode>& other) {
	while (!other.isEmpty()) {
		this->insert(other.back());
		other.deleteTail();
	}
}

template<class DoubleNode>
inline bool DoubleList<DoubleNode>::isEmpty() const {
	return (head_ == nullptr && tail_ == nullptr);
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::swap(DoubleList<DoubleNode>& other) noexcept {
	std::swap(this->head_, other.head_);
	std::swap(this->tail_, other.tail_);
	std::swap(this->size_, other.size_);
}
template<class DoubleNode>
inline DoubleList<DoubleNode>* DoubleList<DoubleNode>::clone() {
	return new DoubleList<DoubleNode>(*this);
}
template<class DoubleNode>
inline void DoubleList<DoubleNode>::clear() {
	while (!isEmpty()) {
		deleteTailNode();
	}
}

#endif


