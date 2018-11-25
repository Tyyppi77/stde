#include <iostream>

#include "stde.h"

enum class Colors {
	White,
	Red,
	Green,
	Blue,
	Black
};
using AllColors = stde::enum_container<Colors, Colors::White, Colors::Black>;
static_assert(AllColors{}.size() == 5);

int main()
{
	for (auto color : AllColors{}) {
		std::cout << static_cast<int>(color) << ", ";
	}

	int result = 0;
	stde::loop_guard::once<> guard;
	for (int i = 2; i < 5; i++) {
		if (guard) {
			result += i;
		}
	}

	bool skipped = false;
	stde::loop_guard::skip_first<> skip{ skipped };
	for (int i = 5; i < 8; i++) {
		if (skip) {
			result += i;
		}
	}
	std::cout << result;  // Outputs 15.
}
