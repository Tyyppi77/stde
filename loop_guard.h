#pragma once

namespace stde {
namespace loop_guard {
	template <bool Initial, bool CompareAgainst>
	struct basic_guard {
		static constexpr bool initial = Initial;
		static constexpr bool compare_against = CompareAgainst;

		constexpr basic_guard() noexcept : m_owned_state(initial), m_state(m_owned_state) { }
		constexpr basic_guard(bool& state) noexcept : m_owned_state(false), m_state(state) { }

		constexpr operator bool() noexcept {
			const bool old = m_state;
			m_state = !initial;
			return old == compare_against;
		}
	protected:
	private:
		bool m_owned_state;
		bool& m_state;
	};

	template <bool Initial = false> using once = basic_guard<Initial, Initial>;
	template <bool Initial = false> using skip_first = basic_guard<Initial, !Initial>;
}
}