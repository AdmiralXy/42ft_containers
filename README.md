## 42ft_containers

### About

Reimplementation of C++98 containers: vector, stack, map. With all member types, public functions and non-member overloads.

### Reimplemented features

* Containers:
  * Vector (boolean space-efficient specialization not implemented)
  * Stack
  * Map


* iterators_traits - template helper struct used to specify all the critical type definitions that an iterator should have.
* reverse_iterator - an adapter that reverses the direction of the given iterator.
* enable_if (C++11 feature) - conditionally instantiates a type to resolve an SFINAE overload.
* is_integral - checks if the type is integer.
* equal - compares the elements in the range, and returns true if all the elements in both ranges match.
* pair - class template that provides a way to store two heterogeneous objects as a single unit.
* make_pair - creates a pair object, deducing the target type from the types of arguments.

### Requirements & usage
Project requires:
* C++ compiler: **c++** or **clang++**
* Makefile

Tested on:
* Linux Ubuntu 20.04

Run:
```
$> make all
$> ./ctests [number_of_entries]
$> ./cbenchmark
```

Makefile commands:
* make / make all / make \[binary_name\] - compile project
* make clean - clean all object files
* make fclean - clean all object files & linked binaries
* make re - recompile project
* make tests - run unit tests
* make leaks - run unit tests with Valgrind leak coverage

### Docs

* Vector - https://www.cplusplus.com/reference/vector/vector/
* Stack - https://www.cplusplus.com/reference/stack/stack/
* Map
  * https://www.cplusplus.com/reference/map/map/
  * https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.1/classstd_1_1map.html
* Other:
  * https://en.cppreference.com/w/cpp/current/iterator_tags
