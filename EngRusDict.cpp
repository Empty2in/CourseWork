#include "EngRusDict.h"
#include "StreamGuard.h"

EngRusDict::EngRusDict() :
	dict_(nullptr),
	count_(0)
{}
EngRusDict::~EngRusDict() {
	this->clear();
}
EngRusDict::EngRusDict(EngRusDict&& other) noexcept{
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

void EngRusDict::insertWord(const std::string& newWord) {
	try {
		/*RBTNode newNode(newWord);
		if (this->isEmpty()) {
			this->dict_ = new RedBlackTree< RBTNode >;
		}
		this->dict_->insert(newWord);*/
		RBTNodePtr newNode = new RBTNode(newWord);
		insertWord(newNode);
		this->count_++;
		delete newNode;
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}
void EngRusDict::insertManyTrans(const std::string& word, const DoubleList<std::string>& newTransl) {
	RBTNodePtr newNodeTransl = this->searchWordNode(word);
	if (newNodeTransl != nullptr) {
		insertManyTrans(newNodeTransl, newTransl);
	}
}

void EngRusDict::insertManyTrans(RBTNodePtr word, const DoubleList<std::string>& newTransl) {
	word->insertManyTransl(newTransl);
}

void EngRusDict::insertWord(RBTNodePtr newWord) {
	try {
		if (this->isEmpty()) {
			this->dict_ = new RedBlackTree< RBTNode >;
		}
		this->dict_->insert(*newWord);
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}

void EngRusDict::insertTranslate(const std::string& word, const std::string& newTransl) {
	RBTNodePtr newNodeTransl = this->searchWordNode(word);
	if (newNodeTransl != nullptr) {
		insertTranslate(newNodeTransl, newTransl);
	}
}
void EngRusDict::insertTranslate(RBTNodePtr word, std::string newTransl) {
	word->insertTranslate(newTransl);
}

bool EngRusDict::searchWord(std::string word) {
	if (this->isEmpty()) {
		return false;
	}
	return this->dict_->search(word);
}

RBTNode EngRusDict::getWordNode(std::string word) const {
	if (this->isEmpty()) {
		throw std::exception("try get wird from empty dict");
	}
	return *(this->searchWordNode(word));
}

DoubleList<std::string>& EngRusDict::getTranslate(std::string word) const {
	RBTNodePtr node = searchWordNode(word);
	if (node == nullptr) {
		throw std::exception("wrong node.");
	}
	return node->getTranslate(word);
}

Color EngRusDict::getNodeColor(std::string word) const {
	if (this->isEmpty()) {
		throw std::exception("empty dict.");
	}
	return this->dict_->getNodeColor(word);
}

size_t EngRusDict::getTranslCount(std::string word) const {
	RBTNodePtr node = searchWordNode(word);
	if (node == nullptr) {
		throw std::exception("wrong node.");
	}
	return node->getTranslCount(word);
}

RBTNode* EngRusDict::searchWordNode(std::string word) const {
	if (this->isEmpty()) {
		return nullptr;
	}
	return  this->dict_->searchKey(word);
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
		delTransl->deleteAllTranslate(word);
	}
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

void EngRusDict::deleteTranslate(std::string word, std::string delTrans) {
	if (this->isEmpty()) {
		return;
	}
	RBTNodePtr delNode = this->searchWordNode(word);
	if (delNode != nullptr) {
		deleteTranslate(delNode, delTrans);
	}
}


void EngRusDict::changeAllTransl(std::string word, const DoubleList<std::string>& newTransl) {
	RBTNodePtr newNodeTransl = this->searchWordNode(word);
	if (newNodeTransl != nullptr) {
		changeAllTransl(newNodeTransl, newTransl);
	}
}

void EngRusDict::changeAllTransl(RBTNodePtr word, const DoubleList<std::string>& newTransl) {
	word->changeAllTransl(newTransl);
}

void EngRusDict::deleteTranslate(RBTNodePtr word, std::string delTrans) {
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
		tree.dict_->preorder();
	}
	return out;
}
