//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//
#include <iostream>

#include "../include/reflect/type_id.hpp"

struct test_struct {
  int i;
  float f;
};

void test_type_id() {
  using namespace volt;

  constexpr type_id default_id;
  constexpr type_id int_id = static_type_id<int>();
  constexpr type_id float_id = static_type_id<float>();
  constexpr type_id test_struct_id = static_type_id<test_struct>();

  static_assert(int_id == static_type_id<int>(),
                "same id should remain the same");
  static_assert(int_id != float_id,
                "different types should have different ids");
}