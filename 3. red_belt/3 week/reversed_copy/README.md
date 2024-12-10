### Programming Assignment: Swap, SortPointers, ReversedCopy

In this task, you need to implement three template functions:

1. `template <typename T> void Swap(T* first, T* second)` — swaps the values pointed to by the pointers `first` and `second`.

2. `template <typename T> void SortPointers(vector<T*>& pointers)` — sorts the pointers based on the values they point to.

3. `template <typename T> void ReversedCopy(T* src, size_t count, T* dst)` — copies in reverse order `count` elements starting from the address in the pointer `src` to the memory area starting at the address `dst`. In this case:

   - Each object in the range `[src; src + count)` should be copied no more than once.
   - Ranges `[src; src + count)` and `[dst; dst + count)` may overlap.
   - Elements in the part of the range `[src; src + count)` that does not intersect with `[dst; dst + count)` should remain unchanged.