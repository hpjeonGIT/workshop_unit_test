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
