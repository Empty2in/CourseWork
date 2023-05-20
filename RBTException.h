#ifndef RBTEXCEPTION_H
#define RBTEXCEPTION_H

#include <exception>

class WrongDeleteKey : public std::exception {
public:
	WrongDeleteKey();
	const char* what() const;
private:
	const char* reason_;
};

class WrongInsertKey : public std::exception {
public:
	WrongInsertKey();
	const char* what() const;
private:
	const char* reason_;
};
#endif
