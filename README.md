# indirect_view

**cursor_iterator**

View an array inexed by another

```
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
```

**segment_iterator**

View subranges of an array defined by adjacent iterators in another

```
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
```

**Combining both**

Using and wrapping both with `std::ranges::subrange` to view an array of variable sized arrays

```
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
```
