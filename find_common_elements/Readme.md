## find common elements b/w two arrays/vectors of different sizes
- Ref: https://stackoverflow.com/questions/4529819/finding-common-elements-in-two-arrays-of-different-size`
  - Sort each vector
  - compare one by one or increase index to match
  - O(N) - or depending on the sorting
```cpp
def common_elements(a, b):
  a.sort()
  b.sort()
  i, j = 0, 0
  common = []
  while i < len(a) and j < len(b):
    if a[i] == b[j]:
      common.append(a[i])
      i += 1
      j += 1
    elif a[i] < b[j]:
      i += 1
    else:
      j += 1
  return common

print 'Common values:', ', '.join(map(str, common_elements([1, 2, 4, 8], [1, 4, 9])))
```
