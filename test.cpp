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
	std::cout << "\n";
	for (auto it = AllColors{}.rbegin(); it != AllColors{}.rend(); ++it) {
		std::cout << static_cast<int>(*it) << ", ";
	}

	int i;
	std::cin >> i;
}
