#pragma once

#include <type_traits>

namespace stde {
	template <typename T, typename Tag>
	struct strong_typedef {
		using type = T;
		static_assert(std::is_trivial_v<type>, "stde::strong_typedef only supports trivial types");

		constexpr explicit strong_typedef(type value) : m_value(value) { }

		constexpr type value() const noexcept { return m_value; }
		constexpr operator type() const noexcept { return m_value; }

		constexpr type operator*() const noexcept { return m_value; }
		constexpr type& operator*() noexcept { return m_value; }
	private:
		type m_value;
	};
}