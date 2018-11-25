# stde

stde (Standard Library Extensions) is a C++17 headers only library containing various utilities that I've found useful.

## stde::enum_container

std::enum_container is a compile-time evaluated container that allows iteration over a continuous enumeration. The usage is super simple, create a helper alias for the type, and iterate over it using a range-based for loop:

```cpp
enum class Colors {
	White,
	Red,
	Green
};
using AllColors = stde::enum_container<Colors, Colors::White, Colors::Green>;

int main()
{
	for (auto color : AllColors{}) {
		std::cout << static_cast<int>(color);
	}
}
```

## constexpr_math.h

The stde implementation needs a constexpr version of `std::abs`, which is implemented in constexpr_math.h as `stde::abs`.
