#include "EngRusDict.h"
#include "StreamGuard.h"

EngRusDict::EngRusDict() :
	dict_(nullptr),
	count_(0)
{}
EngRusDict::~EngRusDict() {
	this->clear();
}
EngRusDict::EngRusDict(const EngRusDict& other) {
	this->count_ = other.count_;
	this->dict_ = other.dict_->clone();
}
EngRusDict::EngRusDict(EngRusDict&& other) noexcept {
	this->dict_ = other.dict_;
	this->count_ = other.count_;
	other.dict_ = nullptr;
	other.count_ = 0;
}
EngRusDict& EngRusDict::operator=(EngRusDict&& other) noexcept {
	if (this != &other) {
		swap(other);
	}
	return *this;
}
EngRusDict& EngRusDict::operator=(const EngRusDict& other) {
	if (this != &other) {
		EngRusDict temp(other);
		swap(temp);
	}
	return *this;
}

void EngRusDict::insertWord(const std::string& newWord) {
	try {
		RBTNodePtr newNode = new RBTNode(newWord);
		insertWord(newNode);
		this->count_++;
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}
void EngRusDict::insertManyTrans(const std::string& word, const DoubleList<std::string>& newTransl) {
	RBTNodePtr newNodeTransl = this->searchWordNode(word);
	insertManyTrans(newNodeTransl, newTransl);
}
void EngRusDict::insertTranslate(const std::string& word, const std::string& newTransl) {
	RBTNodePtr newNodeTransl = this->searchWordNode(word);
	if (newNodeTransl == nullptr) {
		insertWord(word);
	}
	newNodeTransl = this->searchWordNode(word);
	insertTranslate(newNodeTransl, newTransl);
}

void EngRusDict::insertWord(RBTNodePtr newWord) {
	try {
		if (this->isEmpty()) {
			this->dict_ = new RedBlackTree< RBTNode >;
		}
		this->dict_->insert(*newWord);
		delete newWord;
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}

void EngRusDict::insertManyTrans(RBTNodePtr word, const DoubleList< std::string >& newTransl) {
	if (word == nullptr) {
		insertWord(word);
	}
	word->insertManyTransl(newTransl);
}

void EngRusDict::insertTranslate(RBTNodePtr word, std::string newTransl) {
	if (word == nullptr) {
		insertWord(word);
	}
	word->insertTranslate(newTransl);
}

void EngRusDict::changeAllTransl(std::string word, const DoubleList< std::string >& newTransl) {
	if (newTransl.isEmpty()) {
		return;
	}
	RBTNodePtr newNodeTransl = this->searchWordNode(word);
	changeAllTransl(newNodeTransl, newTransl);
}
void EngRusDict::changeAllTransl(RBTNodePtr word, const DoubleList<std::string>& newTransl) {
	if (word == nullptr) {
		insertWord(word);
	}
	word->changeAllTransl(newTransl);
}

bool EngRusDict::searchWord(std::string word) {
	if (this->isEmpty()) {
		return false;
	}
	return this->dict_->search(word);
}
RBTNode* EngRusDict::searchWordNode(std::string word) const {
	if (this->isEmpty()) {
		return nullptr;
	}
	return this->dict_->searchKey(word);
}

void EngRusDict::deleteWord(std::string word) {
	if (this->isEmpty()) {
		return;
	}
	RBTNodePtr delNode = this->searchWordNode(word);
	if (delNode != nullptr) {
		deleteWord(delNode);
		this->count_--;
	}
}
void EngRusDict::deleteAllTransl(std::string word) {
	if (this->isEmpty()) {
		return;
	}
	RBTNodePtr delTransl = this->searchWordNode(word);
	if (delTransl != nullptr) {
		delTransl->deleteAllTranslate();
	}
}
void EngRusDict::deleteTranslate(std::string word, std::string delTrans) {
	if (this->isEmpty()) {
		return;
	}
	RBTNodePtr delNode = this->searchWordNode(word);
	delNode->deleteTranslate(delTrans);
}

void EngRusDict::deleteWord(RBTNodePtr word) {
	if (this->isEmpty()) {
		return;
	}
	this->dict_->deleteNode(*word);
	if (this->dict_->isEmpty()) {
		this->clear();
	}
}
void EngRusDict::deleteTranslate(RBTNodePtr word, std::string delTrans) {
	if (word == nullptr) {
		return;
	}
	word->deleteTranslate(delTrans);
}

bool EngRusDict::isEmpty() const {
	return (this->dict_ == nullptr);
}
void EngRusDict::swap(EngRusDict& other) {
	std::swap(this->dict_, other.dict_);
	std::swap(this->count_, other.count_);
}
void EngRusDict::clear() {
	count_ = 0;
	delete dict_;
	dict_ = nullptr;
}
void EngRusDict::printRBTree() {
	this->dict_->print();
}

RBTNode EngRusDict::getWordNode(std::string word) const {
	if (this->isEmpty()) {
		throw std::exception("nothing there");;
	}
	return *(this->searchWordNode(word));
}
DoubleList< std::string >& EngRusDict::getTranslate(std::string word) const {
	RBTNodePtr node = searchWordNode(word);
	if (node == nullptr) {
		throw std::exception("nothing there");;
	}
	return node->getTranslate(word);
}
Color EngRusDict::getNodeColor(std::string word) const {
	if (this->isEmpty()) {
		throw std::exception("nothing there");;
	}
	return this->dict_->getNodeColor(word);
}
size_t EngRusDict::getTranslCount(std::string word) const {
	RBTNodePtr node = searchWordNode(word);
	if (node == nullptr) {
		throw std::exception("nothing there");
	}
	return node->getTranslCount(word);
}

size_t EngRusDict::getCountOfWord() const {
	return this->count_;
}

std::ostream& operator<<(std::ostream& out, const EngRusDict& tree) {
	std::ostream::sentry sentry(out);
	if (!sentry) {
		return out;
	}
	StreamGuard stream(out);
	if (tree.isEmpty()) {
		out << "Dictionary is empty.\n";
	}
	else {
		std::cout << "Dictionary:\n";
		tree.dict_->inorder();
	}
	return out;
}
