//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//
#include <iostream>

#include "../volt/reflect/type_id.hpp"

struct test_struct {
  int i;
  float f;
};

void test_type_name() {
  using namespace volt;

  constexpr auto float_name = type_name<float>();
  constexpr auto int_name = type_name<int>();
  constexpr auto test_struct_name = type_name<test_struct>();

  static_assert(float_name == "float");
  static_assert(int_name == "int");
  static_assert(type_name<double>() == "double");
  static_assert(type_name<void>() == "void");

  std::cout << float_name << "\n";
  std::cout << int_name << "\n";
  std::cout << test_struct_name << "\n";
}

void test_type_id() {
  using namespace volt;
  constexpr type_id default_id;
  constexpr type_id default_id_constructed{};

  static_assert(default_id == default_id_constructed);

  constexpr type_id int_id = static_type_id<int>();
  constexpr type_id float_id = static_type_id<float>();
  constexpr type_id test_struct_id = static_type_id<test_struct>();

  static_assert(int_id == static_type_id<int>(),
                "same id should remain the same");
  static_assert(int_id != float_id,
                "different types should have different ids");
}

int main() {
  test_type_name();
  test_type_id();
}