#include "RBTNode.h"
#include "StreamGuard.h"

RBTNode::RBTNode() :
	word_(""), 
	transl_(nullptr) 
{}
RBTNode::RBTNode(std::string word) :
	word_(word), 
	transl_(nullptr)
{}
RBTNode::RBTNode(std::string word, DoubleList<std::string> trans) {
	try {
		word_ = word;
		transl_ = new DoubleList<std::string>(trans);
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}
RBTNode::~RBTNode() {
	delete transl_;
}
RBTNode::RBTNode(const RBTNode& other) {
	word_ = other.word_;
	if (other.transl_ != nullptr) {
		transl_ = other.transl_->clone();
	}
	else {
		transl_ = nullptr;
	}
}
RBTNode::RBTNode(RBTNode && other) noexcept {
	word_ = other.word_;
	transl_ = other.transl_;
	other.word_ = "";
	other.transl_ = nullptr;
}
RBTNode& RBTNode::operator=(const RBTNode& other){
	if (this != &other) {
		RBTNode temp(other);
		swap(temp);
	}
	return *this->clone();
}
RBTNode& RBTNode::operator=(RBTNode&& other) noexcept {
	if (this != &other) {
		swap(other);
	}
	return *this;
}

void RBTNode::swap(RBTNode& other) {
	std::swap(this->word_, other.word_);
	std::swap(this->transl_, other.transl_);
}
RBTNode* RBTNode::clone() {
	return new RBTNode(*this);
}

DoubleList<std::string>& RBTNode::getTranslate(const std::string& trans) const {
	return *this->transl_;
}

size_t RBTNode::getTranslCount(const std::string& word) const {
	return this->transl_->size();
}

void RBTNode::insertWord(const std::string& word) {
	this->word_ = word;
}

void RBTNode::insertManyTransl(const DoubleList<std::string>& trans) {
	try {
		if (transl_ != nullptr) {
			return;
		}
		transl_ = new DoubleList<std::string>(trans);
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}

void RBTNode::changeAllTransl(const DoubleList<std::string>& trans) {
	try {
		if (transl_ != nullptr) {
			transl_->clear();
		}
		transl_ = new DoubleList<std::string>(trans);
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}

void RBTNode::insertTranslate(const std::string& trans) {
	try {
		if (this->transl_ == nullptr) {
			transl_ = new DoubleList<std::string>;
		}
		this->transl_->insert(trans);
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error " << e.what();
		exit(-1);
	}
}

void RBTNode::deleteTranslate(const std::string& trans) {
	if (this->transl_ == nullptr || this->transl_->isEmpty()) {
		return;
	}
	this->transl_->deleteKey(trans);
	if (this->transl_->isEmpty()) {
		delete this->transl_;
		this->transl_ = nullptr;
	}
}

void RBTNode::deleteAllTranslate(const std::string& trans) {
	if (this->transl_ == nullptr || this->transl_->isEmpty()) {
		return;
	}
	this->transl_->clear();
	this->transl_ = nullptr;
}

bool operator<(const RBTNode& curr, const RBTNode& other)
{
	return curr.word_ < other.word_;
}
bool operator>(const RBTNode& curr, const RBTNode& other)
{
	return curr.word_ > other.word_;
}
bool operator==(const RBTNode& curr, const RBTNode& other)
{
	return curr.word_ == other.word_;
}
bool operator!=(const RBTNode& curr, const RBTNode& other)
{
	return !(curr == other);
}

std::ostream& operator<<(std::ostream& out, const RBTNode& node) {
	std::ostream::sentry sentry(out);
	if (!sentry) {
		return out;
	}
	StreamGuard stream(out);
	out << node.word_;
	if (node.transl_ != nullptr) {
		std::cout << " - " << *(node.transl_);
	}
	return out;
}
