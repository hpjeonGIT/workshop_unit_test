## Some discussion
- intel icpc may swallow stl::vector into `__mm256_load_pd()`
- g++ needs `aligned_alloc()` for `__mm256_load_pd()`
- g++ may use `__mm256_loadu_pd()` for std::vector, which is not aligned, but the overhead is very high
- May need to find how to align std::vector?

## fma_aligned_alloc.cxx
- Testing regular loop or fma_256 for daxpy such as `z=a*x +y`
- Optimizing -O3 produces the regular loop into fma anyway

## fm_vector.cxx
- Testing std::vector instead of aligned_alloc
- But the overhead of unaligned memory is very high
- Needs to test with icpc. Doe icpc produce fast code even with std::vector?
  - No. g++ produces similar binary of what icpc produces

## call by value vs call by reference
- Call by value:
```
void loop_v(int n, Vec x, Vec y, Vec &z) {
  double pi=3.14;
  for (int=0;i<n;i++) z[i] = pi*x[i] + y[i];
}
```
- Call by reference:
```
void loop_v(int n, Vec const &x, Vec const &y, Vec &z) {
  double pi=3.14;
  for (int=0;i<n;i++) z[i] = pi*x[i] + y[i];
}
```
- Call by value will be 5-6x more expensive than call by reference
