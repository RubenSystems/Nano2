#include <random>
#include <sstream>


namespace UUID {
	const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	std::string uuid() {
		std::string s;
		
		for (int i = 0; i < sizeof(alphanum) / sizeof(alphanum[0]); ++i) {
			s += alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		return s;
	}
}