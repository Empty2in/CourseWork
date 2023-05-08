#ifndef RBTNODE_H
#define RBTNODE_H

#include <string>
#include "DoubleList.h"

class RBTNode {
public:
	RBTNode();
	RBTNode(std::string word);
	RBTNode(std::string word, DoubleList<std::string> trans);
	~RBTNode();
	RBTNode(const RBTNode& other);
	RBTNode(RBTNode&& other) noexcept;
	RBTNode& operator=(const RBTNode& other);
	RBTNode& operator=(RBTNode&& other) noexcept;

	void swap(RBTNode& other);
	RBTNode* clone();

	DoubleList<std::string>& getTranslate(const std::string& trans) const;
	size_t getTranslCount(const std::string& word) const;

	void insertWord(const std::string& word);
	void insertManyTransl(const DoubleList<std::string>& trans);
	void insertTranslate(const std::string& trans);

	void changeAllTransl(const DoubleList<std::string>& trans);

	void deleteTranslate(const std::string& trans);
	void deleteAllTranslate(const std::string& trans);

	/*bool operator<(const RBTNode& other);
	bool operator>(const RBTNode& other);
	bool operator==(const RBTNode& other);
	bool operator!=(const RBTNode& other);*/

	friend bool operator<(const RBTNode& curr, const RBTNode& other);
	friend bool operator>(const RBTNode& curr, const RBTNode& other);
	friend bool operator==(const RBTNode& curr, const RBTNode& other);
	friend bool operator!=(const RBTNode& curr, const RBTNode& other);

	friend std::ostream& operator<<(std::ostream& out, const RBTNode& node);

private:
	std::string word_;
	DoubleList<std::string>* transl_;
};

#endif

