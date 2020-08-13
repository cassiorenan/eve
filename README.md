# Eve
**Eve** is the <em><b>E</b></em>uclidean <em><b>Ve</b></em>ctor Library. Eve requires C++17.

## Usage
Eve is header-only. To use it, you just need to `#include "eve/eve.hpp"`.

## Introduction

Nothing beats an example:

    #include <iostream>
    #include <typeinfo>
    #include "eve/eve.hpp"

    int main() {
      eve::vector a{1.0,2.0,3.0};
      eve::vector b{3,2,1};
      auto sum = a+b;
      auto diffab = a-b;
      auto diffba = b-a;
      auto length_sum = eve::length(sum);
      auto distance = eve::distance(a, b);
      auto dot = eve::dot_product(a, b);

      std::cout
        << "The initial vectors are " << a << " and " << b << ".\n"
        << "The first vector has components of type "
          << typeid(typename decltype(a)::value_type).name() << ".\n"
        << "The second vector has components of type "
          << typeid(typename decltype(b)::value_type).name()
          << ". Results may be truncated because of this.\n"
        << "Their sum is " << sum << " which has length " << length_sum << ".\n"
        << "Their differences are " << diffab << " and " << diffba << ".\n"
        << "They are " << distance << " units apart.\n"
        << "Their dot product is " << dot << ".\n"
        << "Their parallel unit vectors are " << eve::normalize(a) << " and " << eve::normalize(b) << ".\n"
        << "Note how the normalization truncated b to a zero vector, because of its type.\n\n";

      eve::vector c{4.0,5.0};
      auto [x, y] = c;

      std::cout
        << "The third vector is " << c << ".\n"
        << "Its components are " << x << " and " << y << ".\n";
    }

**output:**

    The initial vectors are (1, 2, 3) and (3, 2, 1).
    The first vector has components of type d.
    The second vector has components of type i. Results may be truncated because of this.
    Their sum is (4, 4, 4) which has length 6.9282.
    Their differences are (-2, 0, 2) and (-2, 0, 2).
    They are 2.82843 units apart.
    Their dot product is 10.
    Their parallel unit vectors are (0.267261, 0.534522, 0.801784) and (0, 0, 0).
    Note how the normalization truncated b to a zero vector, because of its type.

    The third vector is (4, 5).
    Its components are 4 and 5.
