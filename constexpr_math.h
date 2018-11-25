#pragma once

namespace stde {
	template <typename T> constexpr T abs(const T& v) noexcept { return (v >= 0) ? v : -v; }
}