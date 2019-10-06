Ref : https://softwareengineering.stackexchange.com/questions/264728/allow-iteration-of-an-internal-vector-without-leaking-the-implementation
- Iterator of neighbor list has been tried while actually they are not used
- Steps
  - mkdir build
  - cd build
  - cmake ..
  - make -j 3
  - sr/md.exe
  - ctest
  - ctest -L base
