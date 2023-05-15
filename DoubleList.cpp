#include "DoubleList.h"
#include "StreamGuard.h"

std::ostream& operator<<(std::ostream& out, const DoubleList< std::string >& node) {
	std::ostream::sentry sentry(out);
	if (!sentry) {
		return out;
	}
	StreamGuard stream(out);
	node.print(out);
	return out;
}
