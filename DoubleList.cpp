#include "DoubleList.h"
#include "StreamGuard.h"

std::ostream& operator<<(std::ostream& out, const DoubleList<std::string>& node) {
	std::ostream::sentry sentry(out);
	if (!sentry) {
		return out;
	}
	StreamGuard stream(out);
	DoubleList<std::string>::NodePtr temp = node.head_;
	while (temp != nullptr && temp != node.tail_) {
		std::cout << temp->key_ << ", ";
		temp = temp->next_;
	}
	std::cout << node.tail_->key_;
	return out;
}
