#ifndef DOUBLELISTEXCEPTION_H
#define DOUBLELISTEXCEPTION_H

#include <exception>

class WrongInsertKeyDL : public std::exception {
public:
	WrongInsertKeyDL();
	const char* what() const;

private:
	const char* reason_;
};

class WrongDeleteKeyDL : public std::exception {
public:
	WrongDeleteKeyDL();
	const char* what() const;
private:
	const char* reason_;
};

class DeleteFromEmptyDL : public std::exception {
public:
	DeleteFromEmptyDL();
	const char* what() const;
private:
	const char* reason_;
};

class DeleteEmptyTailDL : public std::exception {
public:
	DeleteEmptyTailDL();
	const char* what() const;
private:
	const char* reason_;
};

class DeleteEmptyHeadDL : public std::exception {
public:
	DeleteEmptyHeadDL();
	const char* what() const;
private:
	const char* reason_;
};
#endif



