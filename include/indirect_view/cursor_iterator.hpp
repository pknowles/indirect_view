// Copyright (c) 2024 Pyarelal Knowles, MIT License

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <ranges>

namespace iview {

// An iterator over indices ("cursors") that reference items in another
// container. Dereferencing returns iterators into the indirect container.
template <std::ranges::random_access_range Container, std::input_iterator CursorIterator> class cursor_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = std::ranges::iterator_t<Container>;
    using difference_type =
        decltype(std::declval<CursorIterator>() - std::declval<CursorIterator>());
    using reference = value_type;
    using const_reference = reference;

    cursor_iterator() noexcept = default;
    cursor_iterator(const cursor_iterator& other) noexcept = default;
    cursor_iterator& operator=(const cursor_iterator& other) noexcept = default;
    cursor_iterator(Container& container, CursorIterator cursorIterator) noexcept
        : m_container(&container), m_cursorIterator(cursorIterator) {}
    reference operator*() noexcept {
        return std::begin(*m_container) + *m_cursorIterator;
    }

    const_reference operator*() const noexcept {
        return std::begin(*m_container) + *m_cursorIterator;
    }

    reference operator[](difference_type index) noexcept {
        return *(*this + index);
    }

    const_reference operator[](difference_type index) const noexcept {
        return *(*this + index);
    }

    cursor_iterator& operator++() noexcept {
        ++m_cursorIterator;
        return *this;
    }

    cursor_iterator operator++(int) noexcept {
        cursor_iterator temp = *this;
        ++(*this);
        return temp;
    }

    cursor_iterator& operator--() noexcept {
        --m_cursorIterator;
        return *this;
    }

    cursor_iterator operator--(int) noexcept {
        cursor_iterator temp = *this;
        --(*this);
        return temp;
    }

    cursor_iterator& operator+=(difference_type n) noexcept {
        m_cursorIterator += n;
        return *this;
    }

    cursor_iterator operator+(difference_type n) const noexcept {
        cursor_iterator result(*this);
        return result += n;
    }

    friend cursor_iterator operator+(difference_type    n,
                                const cursor_iterator& it) noexcept {
        return it + n;
    }

    cursor_iterator& operator-=(difference_type n) noexcept {
        return *this += (-n);
    }

    cursor_iterator operator-(difference_type n) const noexcept {
        return *this + (-n);
    }

    friend cursor_iterator operator-(difference_type    n,
                                const cursor_iterator& it) noexcept {
        return it - n;
    }

    difference_type operator-(const cursor_iterator& other) const noexcept {
        return std::distance(other.m_cursorIterator, m_cursorIterator);
    }

    bool operator==(const cursor_iterator& other) const noexcept = default;
    auto operator<=>(const cursor_iterator& other) const noexcept {
        return m_cursorIterator <=> other.m_cursorIterator;
    }

private:
    Container* m_container = nullptr;
    CursorIterator m_cursorIterator;
};

template<std::ranges::random_access_range Container, std::input_iterator CursorIterator>
using cursor_range = std::ranges::subrange<cursor_iterator<Container, CursorIterator>>;

// TODO: ownership and const correctness
template<std::ranges::random_access_range Container, std::ranges::input_range CursorRange>
cursor_range<Container, std::ranges::iterator_t<CursorRange>> indirect_view(Container& container, CursorRange&& cursors)
{
    using iterator_type = cursor_iterator<Container, std::ranges::iterator_t<CursorRange>>;
    return {iterator_type{container, std::begin(cursors)}, iterator_type{container, std::end(cursors)}};
}

} // namespace iview
