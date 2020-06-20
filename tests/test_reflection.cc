//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <iostream>
#include <vector>
#include <volt/reflect/type_id.hpp>

struct test_struct {
  int i;
  float f;
};

namespace scope {
struct scoped_test_struct {};
}  // namespace scope

namespace {
struct anon_test_struct {};
}  // namespace

TEST_CASE("Compile-time type_name retrieval", "[type_name]") {
  [[maybe_unused]] constexpr auto float_name = volt::type_name<float>();
  [[maybe_unused]] constexpr auto int_name = volt::type_name<int>();
  [[maybe_unused]] constexpr auto struct_name = volt::type_name<test_struct>();
  [[maybe_unused]] constexpr auto scoped_struct_name =
      volt::type_name<scope::scoped_test_struct>();
  [[maybe_unused]] constexpr auto anon_struct_name =
      volt::type_name<anon_test_struct>();

  SECTION("Equality of basic types") {
    REQUIRE(volt::type_name<float>() == "float");
    REQUIRE(volt::type_name<int>() == "int");
    REQUIRE(volt::type_name<double>() == "double");
    REQUIRE(volt::type_name<void>() == "void");
  }

  SECTION("Non-basic types compilability") {
    REQUIRE(volt::type_name<test_struct>() == volt::type_name<test_struct>());
    REQUIRE(volt::type_name<scope::scoped_test_struct>() ==
            volt::type_name<scope::scoped_test_struct>());
  }

  std::vector<std::string_view> type_names{
      volt::type_name<float>(),
      volt::type_name<int>(),
      volt::type_name<double>(),
      volt::type_name<void>(),
      volt::type_name<test_struct>(),
      volt::type_name<scope::scoped_test_struct>(),
  };

  SECTION("Inequality of types") {
    REQUIRE(std::unique(type_names.begin(), type_names.end()) ==
            type_names.end());
  }
}

TEST_CASE("Compile-time type id", "[type_id]") {
  constexpr auto float_id = volt::static_type_id<float>();
  constexpr auto int_id = volt::static_type_id<int>();
  constexpr auto double_id = volt::static_type_id<double>();
  constexpr auto void_id = volt::static_type_id<void>();
  constexpr auto struct_id = volt::static_type_id<test_struct>();
  constexpr auto scoped_struct_id =
      volt::static_type_id<scope::scoped_test_struct>();
  constexpr auto anon_struct_id = volt::static_type_id<anon_test_struct>();

  SECTION("Equality of basic types") {
    REQUIRE(volt::static_type_id<float>() == float_id);
    REQUIRE(volt::static_type_id<int>() == int_id);
    REQUIRE(volt::static_type_id<double>() == double_id);
    REQUIRE(volt::static_type_id<void>() == void_id);
  }

  SECTION("Non-basic types compilability") {
    REQUIRE(volt::static_type_id<test_struct>() == struct_id);
    REQUIRE(volt::static_type_id<scope::scoped_test_struct>() ==
            scoped_struct_id);
    REQUIRE(volt::static_type_id<anon_test_struct>() == anon_struct_id);
  }

  std::vector<volt::type_id> type_ids{
      volt::static_type_id<float>(),
      volt::static_type_id<int>(),
      volt::static_type_id<double>(),
      volt::static_type_id<void>(),
      volt::static_type_id<test_struct>(),
      volt::static_type_id<scope::scoped_test_struct>(),
  };

  SECTION("Inequality of types") {
    REQUIRE(std::unique(type_ids.begin(), type_ids.end()) == type_ids.end());
  }
}
