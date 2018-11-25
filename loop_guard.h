#pragma once

namespace stde {
namespace loop_guard {
	template <bool Initial = false>
	struct once {
		constexpr once() noexcept : m_owned_state(Initial), m_state(m_owned_state) { }
		constexpr once(bool& state) noexcept : m_owned_state(false), m_state(state) { }

		constexpr operator bool() noexcept { 
			const bool old = m_state;
			m_state = !Initial;
			return old == Initial;
		}
	private:
		bool m_owned_state;
		bool& m_state;
	};
}
}