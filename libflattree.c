#include "libflattree.h"

static inline int is_even(int n)
{
  return n % 2 == 0;
}

static inline int is_odd(int n)
{
  return n % 2 != 0;
}

size_t lft_index(int depth, int offset)
{
  return (offset << depth + 1) | ((1 << depth) - 1);
}

int lft_depth(size_t index)
{
  int depth = 0;

  while (is_odd(index)) {
    index >>= 1;
    depth++;
  }

  return depth;
}

int lft_offset(size_t index)
{
  return lft_offset_2(index, lft_depth(index));
}

int lft_offset_2(size_t index, int depth)
{
  return is_even(index) ? index / 2 : index >> (depth + 1);
}

size_t lft_sibling(size_t index)
{
  return lft_sibling_2(index, lft_depth(index));
}

size_t lft_sibling_2(size_t index, int depth)
{
  return lft_index(depth, lft_offset_2(index, depth) ^ 1);
}

size_t lft_parent(size_t index)
{
  return lft_parent_2(index, lft_depth(index));
}

size_t lft_parent_2(size_t index, int depth)
{
  return lft_index(depth + 1, lft_offset_2(index, depth) >> 1);
}

size_t lft_left_child(size_t index)
{
  return lft_left_child_2(index, lft_depth(index));
}

size_t lft_left_child_2(size_t index, int depth)
{
  if (is_even(index)) return -1;
  return lft_index(depth - 1, lft_offset_2(index, depth) << 1);
}

size_t lft_right_child(size_t index)
{
  return lft_right_child_2(index, lft_depth(index));
}

size_t lft_right_child_2(size_t index, int depth)
{
  if (is_even(index)) return -1;
  return lft_index(depth - 1, 1 + (lft_offset_2(index, depth) << 1));
}

size_t lft_left_span(size_t index)
{
  return lft_left_span_2(index,lft_depth(index));
}

size_t lft_left_span_2(size_t index, int depth)
{
  if (is_even(index)) return index;
  return lft_offset_2(index, depth) * (1 << depth + 1);
}

size_t lft_right_span(size_t index)
{
  return lft_right_span_2(index, lft_depth(index));
}

size_t lft_right_span_2(size_t index, int depth)
{
  if (is_even(index)) return index;
  return (lft_offset_2(index, depth) + 1) * (1 << depth + 1) - 2;
}
