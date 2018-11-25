#pragma once

#include <iterator>
#include <type_traits>

#include "constexpr_math.h"

namespace stde {
	template <typename EnumType>
	struct enum_iterator {
		static_assert(std::is_enum_v<EnumType>, "stde::enum_iterator requires enum types.");

		using enum_type = EnumType;
		using enum_value_type = std::underlying_type_t<EnumType>;

		constexpr enum_iterator(enum_type value) noexcept : m_value(value) { }
		constexpr enum_iterator(const enum_iterator& other) noexcept : m_value(other.m_value) { }
		constexpr enum_iterator(enum_iterator&& other) noexcept : m_value(other.m_value) { }
		~enum_iterator() noexcept = default;

		constexpr enum_iterator& operator=(const enum_iterator& other) noexcept { m_value = other.m_value; return *this; }
		constexpr enum_iterator& operator=(enum_iterator&& other) noexcept { m_value = other.m_value; return *this; }

		constexpr operator enum_type() const { return m_value; }

		constexpr enum_type& operator*() noexcept { return m_value; }
		constexpr const enum_type& operator*() const noexcept { return m_value; }

		constexpr bool operator==(const enum_iterator& other) const noexcept { return m_value == other.m_value; }
		constexpr bool operator!=(const enum_iterator& other) const noexcept { return m_value != other.m_value; }

		constexpr enum_iterator& operator+=(const std::ptrdiff_t diff) noexcept { return alter(diff); }
		constexpr enum_iterator& operator-=(const std::ptrdiff_t diff) noexcept { return alter(-diff); }
		constexpr enum_iterator& operator++() noexcept { return alter(+1); }
		constexpr enum_iterator& operator--() noexcept { return alter(-1); }
		constexpr enum_iterator operator++(int) noexcept { auto old = *this; alter(+1); return old; }
		constexpr enum_iterator operator--(int) noexcept { auto old = *this; alter(-1); return old; }
		constexpr enum_iterator operator+(const std::ptrdiff_t diff) const noexcept { auto ret = *this; return ret.alter(diff); }
		constexpr enum_iterator operator-(const std::ptrdiff_t diff) const noexcept { auto ret = *this; return ret.alter(-diff); }

		constexpr std::ptrdiff_t operator-(const enum_iterator& other) const noexcept { return static_cast<std::ptrdiff_t>(as_value_type() - other.as_value_type()); }
	private:
		constexpr enum_iterator& alter(const int diff) noexcept { m_value = static_cast<enum_type>(static_cast<enum_value_type>(m_value) + diff); return *this; }

		constexpr enum_value_type as_value_type() const noexcept { return static_cast<enum_value_type>(m_value); }

		enum_type m_value;
	};

	template <typename EnumType, EnumType First, EnumType Last> 
	struct enum_container {
		static_assert(std::is_enum_v<EnumType>, "stde::enum_container requires enum types.");

		using enum_type = EnumType;
		using enum_value_type = std::underlying_type_t<enum_type>;

		using iterator = enum_iterator<EnumType>;
		using reverse_iterator = std::reverse_iterator<iterator>;

		static constexpr enum_type first = First;
		static constexpr enum_type last = Last;

		constexpr enum_container() noexcept { }

		constexpr enum_type front() const { return first; }
		constexpr enum_type back() const { return last; }

		constexpr iterator begin() const noexcept { return iterator(first); }
		constexpr iterator end() const noexcept { return iterator(last) + 1; }
		constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }
		constexpr reverse_iterator rend() const noexcept { return reverse_iterator(begin()); }

		constexpr std::size_t size() const noexcept { return static_cast<std::size_t>(stde::abs(end() - begin())); }
	};
}

namespace std {
	template<typename EnumType>
	class iterator_traits<stde::enum_iterator<EnumType>> {
	public:
		using difference_type = std::ptrdiff_t;
		using size_type = std::size_t;
		using value_type = EnumType;
		using pointer = EnumType*;
		using reference = EnumType&;
		using iterator_category = std::random_access_iterator_tag;
	};
}