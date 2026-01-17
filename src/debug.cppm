export module debug;

import std;

export void dbg(std::string msg) {
#ifndef NDEBUG
	std::println("[DBG]: {}", msg);
#endif
}
