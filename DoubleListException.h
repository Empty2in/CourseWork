#ifndef DOUBLELISTEXCEPTION_H
#define DOUBLELISTEXCEPTION_H

#include <exception>

class WrongInsertKeyDL : public std::exception {
public:
	WrongInsertKeyDL() : reason_("Wrong key for insert.") {}
	const char* what() const { return reason_; }

private:
	const char* reason_;
};

class WrongDeleteKeyDL : public std::exception {
public:
	WrongDeleteKeyDL() : reason_("wrong key for delete.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

class DeleteFromEmptyDL : public std::exception {
public:
	DeleteFromEmptyDL() : reason_("delete from empty list.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

class DeleteEmptyTailDL : public std::exception {
public:
	DeleteEmptyTailDL() : reason_("delete empty tail.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

class DeleteEmptyHeadDL : public std::exception {
public:
	DeleteEmptyHeadDL() : reason_("delete empty head.") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};
#endif



