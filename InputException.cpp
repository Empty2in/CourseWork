#include "InputException.h"


IncorrectFile::IncorrectFile() : reason_("incorrrect name of file.") {}
const char* IncorrectFile::what() const { return reason_; }

EmptyFile::EmptyFile() : reason_("file is empty.") {}
const char* EmptyFile::what() const { return reason_; }

WrongWord::WrongWord() : reason_("wrong word.") {}
const char* WrongWord::what() const { return reason_; }

WrongInt::WrongInt() : reason_("wrong number.") {}
const char* WrongInt::what() const { return reason_; }
