#ifndef ENGRUSDICT_H
#define ENGRUSDICT_H

#include "RedBlackTree.h"
#include "RBTNode.h"

class EngRusDict {
public:
	EngRusDict();
	~EngRusDict() = default;
	EngRusDict(const EngRusDict& other);
	EngRusDict(EngRusDict&& other) noexcept;
	EngRusDict& operator=(const EngRusDict& other);
	EngRusDict& operator=(EngRusDict&& other) noexcept;

	RBTNode getWordNode(std::string word);
	DoubleList< std::string > getTranslate(std::string word);
	Color getNodeColor(std::string word);
	size_t getTranslCount(std::string word);
	size_t getCountOfWord() const;

	bool searchWord(std::string word);

	void insertWord(const std::string& newWord);
	void insertManyTrans(const std::string& word, const DoubleList< std::string >& newTransl);
	void insertTranslate(const std::string& word, const std::string& newTransl);

	void deleteWord(std::string word);
	void deleteAllTransl(std::string word);
	void deleteTranslate(std::string word, std::string delTrans);

	void changeAllTransl(std::string word, const DoubleList< std::string >& newTransl);

	bool isEmpty() const;
	void swap(EngRusDict& other);
	void clear();
	void printRBTree(std::ostream& out);

	friend std::ostream& operator<<(std::ostream& out, const EngRusDict& tree);

private:
	RedBlackTree< RBTNode > dict_;
	size_t count_;
	typedef RBTNode* RBTNodePtr;
	RBTNodePtr searchWordNode(std::string word);
};

#endif

