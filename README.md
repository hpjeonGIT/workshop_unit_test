# TDD
Ref: Modern C++ Programming with Test-driven development by Jeff Langr

# Effective Modern C++ by Scott Meyers
- Location 1620: C++ forbids reference to bits - auto in bool might be dangerous
- Location 1745: instead of C-style casting like `(int)d`, use `static_cast<int> (d)`
- Location 1863: uniform initializatio or braced initialization
  - int x(0);
  - int x= 0;
  - int x {0};
  - {} can be used anywhere. x(0) may not work in the class declaration. x=0 may not work for atomic
  - But {} checks type more strictly. Casting or type conversion will work with () or =
  - In overloading of constructors, it will prefer initialization_list
  - std::vector<int> v1(10,20); 10 length vector with value of 20
  - std::vector<int> v1{10,20}; a single vector with 2 elements of 10,20
- Location 2342: typedef => using

# Best practice of C++11
- Pass by value vs pass by const address
  - `f1(double dt)` pass by value. Overhead of data copy. Data will not be changed
  - `fi(double& dt)` pass by address. Data can be changed
  - `f1(const double& dt)` or `f1(double const& dt)` pass by constant address. Recommended
  - Ref: https://softwareengineering.stackexchange.com/questions/372105/is-passing-arguments-as-const-references-premature-optimization
- Using unique pointer
  - Allocate dynamic array using new while delete is not required. Garbage collection
  - Not suitable for MPI communication. Use STL instead
  - Legacy pointer : requires delete
  ```
  int *x;
  x = new int (4);
  ...
  delete[] x;
  ```
  - std::unique_ptr : garbage collection. no delete
  ```
  std::unique_ptr<int[]> v {new int [4]}
  ```
  - Using make_unique (since -std=c++14) : garbage collection. no delete
  ```
  std::unique_ptr<int[]> w;
  w = std::make_unique<int[]>(4);
  ```
  
# Valgrind
- Detection of uninitialized variables are done when the variables are compared
- Assigning uninitialized value is NOT detected

# ctest from cmake
- ctest # run all tests - unit test, regression test, ...
- ctest -L some_test # run some_test among all tests
- ctest -LE some_test # run all tests but some_test
- ctest --timeout 1000 # each test will use time out 1000 sec
- ctest -R my_unit_test_01 # run one set named my_unit_test_01 among all tests
- ctest -VV -R my_unit_test_01 # run one set named my_unit_test01 among all tests. Higher verbosity. stdout will be shown in the screen output
