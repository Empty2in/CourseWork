#include "StreamGuard.h"

StreamGuard::StreamGuard(std::basic_ios<char>& s) :
	s_(s),
	fill_(s.fill()),
	flags_(s.flags()),
	precision_(s.precision())
{}

StreamGuard::~StreamGuard() {
	s_.precision(precision_);
	s_.flags(flags_);
	s_.fill(fill_);
}