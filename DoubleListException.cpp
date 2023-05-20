#include "DoubleListException.h"


WrongInsertKeyDL::WrongInsertKeyDL() : reason_("Wrong key for insert.") {}
const char* WrongInsertKeyDL::what() const { return reason_; }

WrongDeleteKeyDL::WrongDeleteKeyDL() : reason_("wrong key for delete.") {}
const char* WrongDeleteKeyDL::what() const { return reason_; }

DeleteFromEmptyDL::DeleteFromEmptyDL() : reason_("delete from empty list.") {}
const char* DeleteFromEmptyDL::what() const { return reason_; }

DeleteEmptyTailDL::DeleteEmptyTailDL() : reason_("delete empty tail.") {}
const char* DeleteEmptyTailDL::what() const { return reason_; }

DeleteEmptyHeadDL::DeleteEmptyHeadDL() : reason_("delete empty head.") {}
const char* DeleteEmptyHeadDL::what() const { return reason_; }
