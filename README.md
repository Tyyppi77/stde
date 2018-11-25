# stde

stde (Standard Library Extensions) is a C++17 headers only library containing various utilities that I've found useful.

Currently contains:

- [stde::enum_container](#stdeenum_container)
- [stde::loop_guard::once](#stdeloop_guardonce)
- [stde::loop_guard::skip_first](#stdeloop_guardskip_first)
- [stde::strong_typedef](#stdestrong_typedef)

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

## stde::loop_guard

stde::loop_guard provides a variety of helper objects that constrain the execution of code inside loops.

### stde::loop_guard::once

stde::loop_guard::once can be either initialized with an existing state-holding boolean variable, or initialized outside of the loop to prevent code inside a loop executing more than once. The real application is inside objects for code that might get called from the public interface more than once, but should be executed only once.

```cpp
int result = 0;
stde::loop_guard::once<> guard;
for (int i = 2; i < 5; i++) {
	if (guard) {
		result += i;
	}
}
std::cout << result;  // Outputs 2.
```

### stde::loop_guard::skip_first

stde::loop_guard::skip_first behaves just like stde::loop_guard::once, but instead of only executing the first iteration, it skips the first iteration but executes all the rest. It can also be default constructed, or initialized with a state-holding boolean.

```cpp
int result = 0;
stde::loop_guard::skip_first<> guard;
for (int i = 2; i < 5; i++) {
	if (guard) {
		result += i;
	}
}
std::cout << result;  // Outputs 7.
```

## stde::strong_typedef

stde::strong_typedef is a simple wrapper class for trivial types that can be used to provide a typesafe alternative to traditional using-statements.

```cpp
using channel = stde::strong_typedef<int, struct channel_tag>;

void foo(channel c) {
	std::cout << *c;
}

int main() {
	foo(12);  // Compile time error.
	foo(channel{ 12 });  // Ok.
}
```