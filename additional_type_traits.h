#pragma once

#include <type_traits>

namespace stde {
	template <typename T> using no_infer = std::common_type_t<T>;
}