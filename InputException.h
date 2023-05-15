#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H
#include <exception>

class IncorrectFile : public std::exception {
public:
	IncorrectFile() : reason_("incorrrect name of file.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

class EmptyFile : public std::exception {
public:
	EmptyFile() : reason_("file is empty.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

class WrongWord : public std::exception {
public:
	WrongWord() : reason_("wrong word.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

class WrongInt : public std::exception {
public:
	WrongInt() : reason_("wrong number.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

#endif