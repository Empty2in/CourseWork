#include "RBTException.h"


WrongDeleteKey::WrongDeleteKey() : reason_("wrong key for delete in RBtree.") {}
const char* WrongDeleteKey::what() const { return reason_; }

WrongInsertKey::WrongInsertKey() : reason_("wrong key for insert in RBtree.") {}
const char* WrongInsertKey::what() const { return reason_; }
