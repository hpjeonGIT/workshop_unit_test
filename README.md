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
