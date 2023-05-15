#include "RBTNode.h"
#include "StreamGuard.h"
#include <iomanip>

RBTNode::RBTNode(std::string word, DoubleList< std::string > trans) {
	word_ = word;
	transl_ = trans;
}

RBTNode::RBTNode(const RBTNode& other) {
	word_ = other.word_;
	transl_ = other.transl_;
}
RBTNode::RBTNode(RBTNode && other) noexcept {
	word_ = other.word_;
	transl_ = other.transl_;
	other.word_ = "";
	other.transl_.clear();
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

DoubleList<std::string> RBTNode::getTranslate(const std::string& trans) {
	DoubleList<std::string> translete = this->transl_;
	return translete;
}
size_t RBTNode::getTranslCount(const std::string& word) const {
	return (this->transl_.size());
}

void RBTNode::insertWord(const std::string& word) {
	this->word_ = word;
}
void RBTNode::insertManyTransl(const DoubleList<std::string>& trans) {
	if (!transl_.isEmpty()) {
		return;
	}
	transl_ = trans;
}
void RBTNode::insertTranslate(const std::string& trans) {
	transl_.insert(trans);
}

void RBTNode::changeAllTransl(const DoubleList<std::string>& trans) {
	transl_ = trans;
}

void RBTNode::deleteTranslate(const std::string& trans) {
	if (transl_.isEmpty()) {
		return;
	}
	transl_.deleteKey(trans);
}
void RBTNode::deleteAllTranslate() {
	transl_.clear();
}

RBTNode* RBTNode::clone() {
	return (new RBTNode(*this));
}
void RBTNode::swap(RBTNode& other) {
	std::swap(this->word_, other.word_);
	std::swap(this->transl_, other.transl_);
}

bool operator<(const RBTNode& curr, const RBTNode& other) {
	return (curr.word_ < other.word_);
}
bool operator>(const RBTNode& curr, const RBTNode& other) {
	return (curr.word_ > other.word_);
}
bool operator==(const RBTNode& curr, const RBTNode& other) {
	return (curr.word_ == other.word_);
}
bool operator!=(const RBTNode& curr, const RBTNode& other) {
	return (!(curr == other));
}

std::ostream& operator<<(std::ostream& out, const RBTNode& node) {
	std::ostream::sentry sentry(out);
	if (!sentry) {
		return out;
	}
	StreamGuard stream(out);
	out << '\t' << std::setw(20) << std::left << node.word_;
	if (!node.transl_.isEmpty()) {
		out << node.transl_;
	}
	return out;
}
