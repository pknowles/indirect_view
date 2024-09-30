// Copyright (c) 2024 Pyarelal Knowles, MIT License

#include <cstring>
#include <gtest/gtest.h>
#include <indirect_view/cursor_iterator.hpp>
#include <indirect_view/segment_iterator.hpp>
#include <vector>

using namespace iview;

TEST(CursorSegments, HappyIteratorIntegration) {
    std::vector<int> items{0, 1, 2, 3, 4, 5};
    std::vector<int> segmentOffsets{0, 2, 2, 3, 6};
    cursor_iterator segmentOffsetsBegin(items, std::begin(segmentOffsets));
    cursor_iterator segmentOffsetsEnd(items, std::end(segmentOffsets));
    segment_iterator<cursor_iterator<std::vector<int>, std::vector<int>::iterator>> segmentBegin(segmentOffsetsBegin);
    segment_iterator<cursor_iterator<std::vector<int>, std::vector<int>::iterator>> segmentEnd(std::prev(segmentOffsetsEnd));
    auto it = segmentBegin;
    EXPECT_NE(it, segmentEnd);
    auto segment0 = *it++;
    EXPECT_EQ(std::ranges::size(segment0), 2);
    EXPECT_EQ(segment0[0], 0);
    EXPECT_EQ(segment0[1], 1);
    EXPECT_NE(it, segmentEnd);
    auto segment1 = *it++;
    EXPECT_EQ(std::ranges::size(segment1), 0);
    EXPECT_NE(it, segmentEnd);
    auto segment2 = *it++;
    EXPECT_EQ(std::ranges::size(segment2), 1);
    EXPECT_EQ(segment2[0], 2);
    EXPECT_NE(it, segmentEnd);
    auto segment3 = *it++;
    EXPECT_EQ(std::ranges::size(segment3), 3);
    EXPECT_EQ(segment3[0], 3);
    EXPECT_EQ(segment3[1], 4);
    EXPECT_EQ(segment3[2], 5);
    EXPECT_EQ(it, segmentEnd);
}

TEST(CursorSegments, HappyRangeIntegration) {
    std::vector<int> items{0, 1, 2, 3, 4, 5};
    std::vector<int> segmentOffsets{0, 2, 2, 3, 6};
    cursor_range<std::vector<int>, std::vector<int>::iterator>
        segmentStartIterators = indirect_view(items, segmentOffsets);
    segment_range<cursor_iterator<std::vector<int>, std::vector<int>::iterator>>
        segments = segments_view(segmentStartIterators);
    auto segmentBegin(std::begin(segments));
    auto segmentEnd(std::end(segments));
    auto it = segmentBegin;
    EXPECT_NE(it, segmentEnd);
    auto segment0 = *it++;
    EXPECT_EQ(std::ranges::size(segment0), 2);
    EXPECT_EQ(segment0[0], 0);
    EXPECT_EQ(segment0[1], 1);
    EXPECT_NE(it, segmentEnd);
    auto segment1 = *it++;
    EXPECT_EQ(std::ranges::size(segment1), 0);
    EXPECT_NE(it, segmentEnd);
    auto segment2 = *it++;
    EXPECT_EQ(std::ranges::size(segment2), 1);
    EXPECT_EQ(segment2[0], 2);
    EXPECT_NE(it, segmentEnd);
    auto segment3 = *it++;
    EXPECT_EQ(std::ranges::size(segment3), 3);
    EXPECT_EQ(segment3[0], 3);
    EXPECT_EQ(segment3[1], 4);
    EXPECT_EQ(segment3[2], 5);
    EXPECT_EQ(it, segmentEnd);
}

TEST(CursorSegments, HappyRangeIntegrationShort) {
    std::vector<int> items{0, 1, 2, 3, 4, 5};
    std::vector<int> segmentOffsets{0, 2, 2, 3, 6};
    std::span<int> segment0 =
        segments_view(indirect_view(items, segmentOffsets))[0];
    std::span<int> segment1 =
        segments_view(indirect_view(items, segmentOffsets))[1];
    std::span<int> segment2 =
        segments_view(indirect_view(items, segmentOffsets))[2];
    std::span<int> segment3 =
        segments_view(indirect_view(items, segmentOffsets))[3];
    EXPECT_EQ(std::ranges::size(segment0), 2);
    EXPECT_EQ(segment0[0], 0);
    EXPECT_EQ(segment0[1], 1);
    EXPECT_EQ(std::ranges::size(segment1), 0);
    EXPECT_EQ(std::ranges::size(segment2), 1);
    EXPECT_EQ(segment2[0], 2);
    EXPECT_EQ(std::ranges::size(segment3), 3);
    EXPECT_EQ(segment3[0], 3);
    EXPECT_EQ(segment3[1], 4);
    EXPECT_EQ(segment3[2], 5);
}
