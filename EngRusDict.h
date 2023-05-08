#ifndef ENGRUSDICT_H
#define ENGRUSDICT_H

#include "RedBlackTree.h"
#include "RBTNode.h"

class EngRusDict {
public:
	EngRusDict();
	~EngRusDict();
	EngRusDict(const EngRusDict& other) = delete;
	EngRusDict(EngRusDict&& other) noexcept;
	EngRusDict& operator=(const EngRusDict& other) = delete;
	EngRusDict& operator=(EngRusDict&& other) noexcept;


	RBTNode getWordNode(std::string word) const;
	DoubleList<std::string>& getTranslate(std::string word) const;
	Color getNodeColor(std::string word) const;
	size_t getTranslCount(std::string word) const;


	bool searchWord(std::string word);

	void insertWord(const std::string& newWord);
	void insertManyTrans(const std::string& word, const DoubleList<std::string>& newTransl);
	void insertTranslate(const std::string& word, const std::string& newTransl);

	void deleteWord(std::string word);
	void deleteAllTransl(std::string word);
	void deleteTranslate(std::string word, std::string delTrans);

	void changeAllTransl(std::string word, const DoubleList<std::string>& newTransl);

	friend std::ostream& operator<<(std::ostream& out, const EngRusDict& tree);

	bool isEmpty() const;
	void swap(EngRusDict& other);
	void clear();
	//EngRusDict copyDict();
	//void printRBTree();

private:
	RedBlackTree< RBTNode >* dict_;
	size_t count_;
	typedef RBTNode* RBTNodePtr;

	void insertWord(RBTNodePtr newWord);
	void insertTranslate(RBTNodePtr word, std::string newTransl);
	void insertManyTrans(RBTNodePtr word, const DoubleList<std::string>& newTransl);

	void changeAllTransl(RBTNodePtr word, const DoubleList<std::string>& newTransl);

	RBTNode* searchWordNode(std::string word) const;

	void deleteWord(RBTNodePtr word);
	void deleteTranslate(RBTNodePtr word, std::string delTrans);
};

#endif

