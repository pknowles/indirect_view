// Copyright (c) 2024 Pyarelal Knowles, MIT License

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <ranges>

namespace iview {

template <std::input_iterator IteratorIterator>
    requires std::input_iterator<std::iter_value_t<IteratorIterator>>
class segment_iterator {
public:
    using value_type        = std::ranges::subrange<std::iter_value_t<IteratorIterator>>;
    using difference_type   = typename std::incrementable_traits<IteratorIterator>::difference_type;
    using reference         = value_type;
    using const_reference   = reference;

    segment_iterator() noexcept                                    = default;
    segment_iterator(const segment_iterator& other) noexcept            = default;
    segment_iterator& operator=(const segment_iterator& other) noexcept = default;
    segment_iterator(IteratorIterator start) noexcept : m_start(start) {}

    reference operator*() noexcept {
        return std::ranges::subrange(*m_start, *std::next(m_start));
    }

    const_reference operator*() const noexcept {
        return std::ranges::subrange(*m_start, *std::next(m_start));
    }

    reference operator[](difference_type index) noexcept {
        return *(*this + index);
    }

    const_reference operator[](difference_type index) const noexcept {
        return *(*this + index);
    }

    segment_iterator& operator++() noexcept {
        ++m_start;
        return *this;
    }

    segment_iterator operator++(int) noexcept {
        segment_iterator temp = *this;
        ++(*this);
        return temp;
    }

    segment_iterator& operator--() noexcept {
        --m_start;
        return *this;
    }

    segment_iterator operator--(int) noexcept {
        segment_iterator temp = *this;
        --(*this);
        return temp;
    }

    segment_iterator& operator+=(difference_type n) noexcept {
        m_start += n;
        return *this;
    }

    segment_iterator operator+(difference_type n) const noexcept {
        segment_iterator result(*this);
        return result += n;
    }

    friend segment_iterator operator+(difference_type    n,
                                const segment_iterator& it) noexcept {
        return it + n;
    }

    segment_iterator& operator-=(difference_type n) noexcept {
        return *this += (-n);
    }

    segment_iterator operator-(difference_type n) const noexcept {
        return *this + (-n);
    }

    friend segment_iterator operator-(difference_type    n,
                                const segment_iterator& it) noexcept {
        return it - n;
    }

    difference_type operator-(const segment_iterator& other) const noexcept {
        return std::distance(other.m_start, m_start);
    }

    auto operator<=>(const segment_iterator& other) const noexcept = default;

private:
    IteratorIterator m_start;
};


template <std::input_iterator IteratorIterator>
using segment_range = std::ranges::subrange<segment_iterator<IteratorIterator>>;

// TODO: ownership/lifetimes and const correctness
template <std::ranges::input_range IteratorRange>
segment_range<std::ranges::iterator_t<IteratorRange>> segments_view(IteratorRange&& segments)
{
    return {std::begin(segments), std::prev(std::end(segments))};
}

} // namespace iview
