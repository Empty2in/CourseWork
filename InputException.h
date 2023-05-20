#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H
#include <exception>

class IncorrectFile : public std::exception {
public:
	IncorrectFile();
	const char* what() const;
private:
	const char* reason_;
};

class EmptyFile : public std::exception {
public:
	EmptyFile();
	const char* what() const;
private:
	const char* reason_;
};

class WrongWord : public std::exception {
public:
	WrongWord();
	const char* what() const;
private:
	const char* reason_;
};

class WrongInt : public std::exception {
public:
	WrongInt();
	const char* what() const;
private:
	const char* reason_;
};

#endif