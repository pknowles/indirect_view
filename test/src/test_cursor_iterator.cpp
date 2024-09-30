// Copyright (c) 2024 Pyarelal Knowles, MIT License

#include <cstring>
#include <gtest/gtest.h>
#include <indirect_view/cursor_iterator.hpp>

using namespace iview;

TEST(CursorIterator, DefaultConstructorArray) {
    [[maybe_unused]] cursor_iterator<int[4], int*> it;
}

TEST(CursorIterator, DefaultConstructorVector) {
    [[maybe_unused]] cursor_iterator<std::vector<int>, std::vector<int>::iterator> it;
}

TEST(CursorIterator, Empty) {
    std::vector<int> items;
    std::vector<int> selection;
    cursor_iterator begin(items, std::begin(selection));
    cursor_iterator end(items, std::end(selection));
    EXPECT_EQ(begin, end);
    EXPECT_EQ(std::distance(begin, end), 0);
}

TEST(CursorIterator, ConstructorArray) {
    int items[]{3, 5, 7, 11};
    int selection[]{3, 1};
    cursor_iterator begin(items, std::begin(selection));
    cursor_iterator end(items, std::end(selection));
    EXPECT_NE(begin, end);
    EXPECT_EQ(std::distance(begin, end), 2);
    EXPECT_EQ(**begin, 11);
    EXPECT_EQ(**std::next(begin), 5);
}

TEST(CursorIterator, ConstructorVector) {
    std::vector<int> items{3, 5, 7, 11};
    std::vector<int> selection{3, 1};
    cursor_iterator begin(items, std::begin(selection));
    cursor_iterator end(items, std::end(selection));
    EXPECT_NE(begin, end);
    EXPECT_EQ(std::distance(begin, end), 2);
    auto it = begin;
    std::vector<int>::iterator first = *it++;
    std::vector<int>::iterator second = *it++;
    EXPECT_EQ(*first, 11);
    EXPECT_EQ(*second, 5);
    EXPECT_EQ(it, end);
}

TEST(IndirectView, ConstructorVector) {
    std::vector<int> items{3, 5, 7, 11};
    std::vector<int> selection{3, 1};
    cursor_range<std::vector<int>, std::vector<int>::iterator> selectedItems =
        indirect_view(items, selection);
    EXPECT_EQ(std::ranges::size(selectedItems), 2);
    auto it = std::begin(selectedItems);
    std::vector<int>::iterator first = *it++;
    std::vector<int>::iterator second = *it++;
    EXPECT_EQ(*first, 11);
    EXPECT_EQ(*second, 5);
    EXPECT_EQ(it, std::end(selectedItems));
}
