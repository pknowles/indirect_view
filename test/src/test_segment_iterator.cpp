// Copyright (c) 2024 Pyarelal Knowles, MIT License

#include <cstring>
#include <gtest/gtest.h>
#include <indirect_view/segment_iterator.hpp>
#include <vector>

using namespace iview;

TEST(SegmentIterator, DefaultConstructorArray) {
    [[maybe_unused]] segment_iterator<int**> it;
}

TEST(SegmentIterator, DefaultConstructorVector) {
    [[maybe_unused]] segment_iterator<std::vector<std::vector<int>::iterator>::iterator> it;
}

TEST(SegmentIterator, ConstructorArray) {
    int items[]{0, 1, 2, 3};
    int* offsets[]{items, items + 2, items + 4};
    [[maybe_unused]] segment_iterator<int**> it(&offsets[0]);
}

TEST(SegmentIterator, ConstructorVector) {
    std::vector<int> items{0, 1, 2, 3};
    std::vector offsets{items.begin(), items.begin() + 2, items.end()};
    [[maybe_unused]] segment_iterator<std::vector<std::vector<int>::iterator>::iterator> it(offsets.begin());
}

TEST(SegmentIterator, EmptyNull) {
    segment_iterator<int**> begin(nullptr), end(nullptr);
    EXPECT_EQ(begin, end);
}

TEST(SegmentIterator, EmptyPtr) {
    int* ptr = nullptr;
    segment_iterator<int**> begin(&ptr), end(&ptr);
    EXPECT_EQ(begin, end);
}

TEST(SegmentIterator, Value) {
    int items[]{0, 1};
    int* segments[]{&items[0], &items[2]};
    segment_iterator<int**> begin(&segments[0]), end(&segments[1]);
    EXPECT_NE(begin, end);
    auto segment0 = *begin;
    EXPECT_EQ(std::ranges::size(segment0), 2);
    EXPECT_EQ(segment0[0], 0);
    EXPECT_EQ(segment0[1], 1);
}

TEST(SegmentIterator, Multiple) {
    int items[]{0, 1, 2};
    int* segments[]{&items[0], &items[2], &items[3]};
    segment_iterator<int**> begin(&segments[0]), end(&segments[2]);
    EXPECT_EQ(std::ranges::distance(begin, end), 2);
    auto it = begin;
    EXPECT_NE(it, end);
    auto segment0 = *it++;
    EXPECT_NE(it, end);
    auto segment1 = *it++;;
    EXPECT_EQ(it, end);
    EXPECT_EQ(std::ranges::size(segment0), 2);
    EXPECT_EQ(segment0[0], 0);
    EXPECT_EQ(segment0[1], 1);
    EXPECT_EQ(std::ranges::size(segment1), 1);
    EXPECT_EQ(segment1[0], 2);
}

TEST(SegmentRange, ConstructorVector) {
    std::vector<int> items{0, 1, 2};
    std::vector<std::vector<int>::iterator> segmentIterators{
        items.begin(), items.begin() + 2, items.end()};
    segment_range<std::vector<std::vector<int>::iterator>::iterator> segments =
        segments_view(segmentIterators);
    EXPECT_EQ(std::ranges::size(segments), 2);
    auto it = std::begin(segments);
    std::span<int> segment0 = *it++;
    std::span<int> segment1 = *it++;
    EXPECT_EQ(segment0.size(), 2);
    EXPECT_EQ(segment0[0], 0);
    EXPECT_EQ(segment0[1], 1);
    EXPECT_EQ(segment1.size(), 1);
    EXPECT_EQ(segment1[0], 2);
}
