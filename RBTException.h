#ifndef RBTEXCEPTION_H
#define RBTEXCEPTION_H

#include <exception>

class WrongDeleteKey : public std::exception {
public:
	WrongDeleteKey() : reason_("wrong key for delete in RBtree.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

class WrongInsertKey : public std::exception {
public:
	WrongInsertKey() : reason_("wrong key for insert in RBtree.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};
#endif
