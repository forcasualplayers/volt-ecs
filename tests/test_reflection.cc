//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <iostream>
#include <vector>
#include <volt/reflect/property.hpp>
#include <volt/reflect/type_id.hpp>
#include <volt/reflect/type_meta.hpp>
#include <volt/reflect/variant.hpp>

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

TEST_CASE("Test variant", "[variant]") {
  volt::reflect::variant v;
  SECTION("Test empty variant") {
    REQUIRE(v.valid() == false);
    REQUIRE(v.contains_value() == false);
    REQUIRE(v.contains_reference() == false);
    REQUIRE(v.contains_const() == false);
    REQUIRE(v.id() == volt::type_id{});
    REQUIRE(v.get_if<int>() == nullptr);
  }

  volt::reflect::variant int_variant{1};
  SECTION("Test int variant") {
    REQUIRE(int_variant.valid() == true);
    REQUIRE(int_variant.contains_value() == true);
    REQUIRE(int_variant.contains_reference() == false);
    REQUIRE(int_variant.contains_const() == false);
    REQUIRE(int_variant.id() == volt::static_type_id<int>());
    REQUIRE(int_variant.get_if<int>());
    REQUIRE(*int_variant.get_if<int>() == 1);
    REQUIRE(int_variant.get_if<float>() == nullptr);

    auto int_variant_copy = int_variant;
    REQUIRE(int_variant_copy.valid() == true);
    REQUIRE(int_variant_copy.contains_value() == true);
    REQUIRE(int_variant_copy.contains_reference() == false);
    REQUIRE(int_variant_copy.contains_const() == false);
    REQUIRE(int_variant_copy.id() == volt::static_type_id<int>());
    REQUIRE(int_variant_copy.get_if<int>());
    REQUIRE(*int_variant_copy.get_if<int>() == 1);
    REQUIRE(int_variant_copy.get_if<float>() == nullptr);
  }

  int i = 2;
  volt::reflect::variant int_ref_variant{i};
  SECTION("Test int ref variant") {
    REQUIRE(int_ref_variant.valid() == true);
    REQUIRE(int_ref_variant.contains_value() == false);
    REQUIRE(int_ref_variant.contains_reference() == true);
    REQUIRE(int_ref_variant.contains_const() == false);
    REQUIRE(int_ref_variant.id() == volt::static_type_id<int>());
    REQUIRE(int_ref_variant.get_if<int>());
    REQUIRE(*int_ref_variant.get_if<int>() == 2);
    REQUIRE(int_ref_variant.get_if<float>() == nullptr);
    i = 3;
    REQUIRE(*int_ref_variant.get_if<int>() == 3);
    REQUIRE(int_ref_variant.get_if<float>() == nullptr);

    auto int_ref_variant_copy = int_ref_variant;
    REQUIRE(*int_ref_variant_copy.get_if<int>() == 3);
    REQUIRE(int_ref_variant_copy.get_if<float>() == nullptr);
  }

  const int ci = 3;
  volt::reflect::variant const_int_ref_variant{ci};
  SECTION("Test const int ref variant") {
    REQUIRE(const_int_ref_variant.valid() == true);
    REQUIRE(const_int_ref_variant.contains_value() == false);
    REQUIRE(const_int_ref_variant.contains_reference() == true);
    REQUIRE(const_int_ref_variant.contains_const() == true);
    REQUIRE(const_int_ref_variant.id() == volt::static_type_id<int>());
    REQUIRE(const_int_ref_variant.get_if<int>() == nullptr);
    REQUIRE(*const_int_ref_variant.get_if<const int>() == 3);
    REQUIRE(const_int_ref_variant.is<int>());
    REQUIRE(const_int_ref_variant.is<const int>());
    REQUIRE(const_int_ref_variant.get_if<float>() == nullptr);
  }
}

TEST_CASE("Test properties", "[property]") {
  struct Vector {
    float x, y, z;
  };
  Vector v{1, 2, 3};
  volt::reflect::variant vector_variant{v};
  volt::reflect::property x_prop{"x", &Vector::x};

  SECTION("Check property's properties") {
    REQUIRE(x_prop.name() == "x");
    REQUIRE(x_prop.type() == volt::static_type_id<float>());
    REQUIRE(x_prop.declaring_type() == volt::static_type_id<Vector>());
  }

  SECTION("Check property getter") {
    auto get_val = x_prop.get_value(vector_variant);
    REQUIRE(get_val.id() == volt::static_type_id<float>());
    REQUIRE(*get_val.get_if<float>() == 1);
    v.x = 4;
    REQUIRE(v.y == 2);
    REQUIRE(v.z == 3);
    REQUIRE(*get_val.get_if<float>() != 4);
    REQUIRE(*x_prop.get_value(vector_variant).get_if<float>() == 4);
  }

  SECTION("Check property setter") {
    v.x = 5;
    x_prop.set_value(vector_variant, 6.f);
    REQUIRE(v.x == 6);
    REQUIRE(*x_prop.get_value(vector_variant).get_if<float>() == 6);
  }
}

TEST_CASE("Test type_meta", "[type meta]") {
  struct TestStruct {
    int i;
    float f;
  };

  volt::reflect::type_meta meta{volt::type_name<TestStruct>(),
                                volt::static_type_id<TestStruct>(),
                                alignof(TestStruct), sizeof(TestStruct)};
  meta.register_property(volt::reflect::property{"i", &TestStruct::i});
  meta.register_property(volt::reflect::property{"f", &TestStruct::f});

  SECTION("Check attributes") {
    REQUIRE(meta.align() == alignof(TestStruct));
    REQUIRE(meta.size() == sizeof(TestStruct));
    REQUIRE(meta.name() == volt::type_name<TestStruct>());
  }

  TestStruct ts;
  ts.i = int(5);
  ts.f = 7.5f;

  volt::reflect::variant var{ts};

  for (const auto& prop : meta.properties()) {
    auto val = prop.get_value(ts);
    if (prop.name() == "i") {
      auto* int_val = val.get_if<int>();
      REQUIRE(int_val);
      REQUIRE(*int_val == 5);
    } else if (prop.name() == "f") {
      auto* float_val = val.get_if<float>();
      REQUIRE(float_val);
      REQUIRE(*float_val == 7.5);
    }
  }
}