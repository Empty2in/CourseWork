#include "EngRusDict.h"
#include "StreamGuard.h"

EngRusDict::EngRusDict() :
	dict_(),
	count_(0)
{}
EngRusDict::EngRusDict(const EngRusDict& other) {
	this->count_ = other.count_;
	this->dict_ = other.dict_;
}
EngRusDict::EngRusDict(EngRusDict&& other) noexcept {
	this->dict_ = other.dict_;
	this->count_ = other.count_;
	other.dict_.clear();
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
		this->dict_.insert(*newNode);
		delete newNode;
		this->count_++;
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}
void EngRusDict::insertManyTrans(const std::string& word, const DoubleList<std::string>& newTransl) {
	RBTNodePtr newNodeTransl = this->searchWordNode(word);
	if (newNodeTransl == nullptr) {
		insertWord(word);
	}
	newNodeTransl = this->searchWordNode(word);
	newNodeTransl->insertManyTransl(newTransl);
}
void EngRusDict::insertTranslate(const std::string& word, const std::string& newTransl) {
	RBTNodePtr newNodeTransl = this->searchWordNode(word);
	if (newNodeTransl == nullptr) {
		insertWord(word);
	}
	newNodeTransl = this->searchWordNode(word);
	newNodeTransl->insertTranslate(newTransl);
}

void EngRusDict::changeAllTransl(std::string word, const DoubleList< std::string >& newTransl) {
	if (newTransl.isEmpty()) {
		return;
	}
	RBTNodePtr newNodeTransl = this->searchWordNode(word);
	if (newNodeTransl == nullptr) {
		return;
	}
	newNodeTransl->changeAllTransl(newTransl);
}

bool EngRusDict::searchWord(std::string word) {
	if (this->isEmpty()) {
		return false;
	}
	return this->dict_.search(word);
}
EngRusDict::RBTNodePtr EngRusDict::searchWordNode(std::string word) {
	if (this->isEmpty()) {
		return nullptr;
	}
	return this->dict_.searchKey(word);
}

void EngRusDict::deleteWord(std::string word) {
	if (this->isEmpty()) {
		return;
	}
	RBTNodePtr delNode = this->searchWordNode(word);
	if (delNode != nullptr) {
		this->dict_.deleteNode(*delNode);
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

bool EngRusDict::isEmpty() const {
	return (this->dict_.isEmpty());
}
void EngRusDict::swap(EngRusDict& other) {
	std::swap(this->dict_, other.dict_);
	std::swap(this->count_, other.count_);
}
void EngRusDict::clear() {
	count_ = 0;
	dict_.clear();
}
void EngRusDict::printRBTree(std::ostream& out) {
	this->dict_.print(out);
}

RBTNode EngRusDict::getWordNode(std::string word) {
	if (this->isEmpty()) {
		throw std::exception("nothing there");;
	}
	return *(this->searchWordNode(word));
}
DoubleList< std::string > EngRusDict::getTranslate(std::string word) {
	RBTNodePtr node = searchWordNode(word);
	if (node == nullptr) {
		return DoubleList< std::string >();
	}
	return node->getTranslate(word);
}
Color EngRusDict::getNodeColor(std::string word) {
	if (this->isEmpty()) {
		throw std::exception("nothing there");;
	}
	return this->dict_.getNodeColor(word);
}
size_t EngRusDict::getTranslCount(std::string word) {
	RBTNodePtr node = searchWordNode(word);
	if (node == nullptr) {
		return 0;
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
		out << "Dictionary:\n";
		tree.dict_.inorder(out);
	}
	return out;
}
