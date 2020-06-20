//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//
#ifndef VOLT_TYPE_ID_HPP_
#define VOLT_TYPE_ID_HPP_

#include <string_view>

#include "type_name.hpp"

namespace volt {
class type_id {
 public:
  using rep_t = size_t;

  constexpr type_id() noexcept;

 private:
  rep_t value_;

  constexpr explicit type_id(rep_t val) noexcept;

  friend constexpr bool operator==(type_id, type_id) noexcept;
  friend constexpr bool operator!=(type_id, type_id) noexcept;
  friend constexpr bool operator<(type_id, type_id) noexcept;
  friend constexpr bool operator<=(type_id, type_id) noexcept;
  friend constexpr bool operator>(type_id, type_id) noexcept;
  friend constexpr bool operator>=(type_id, type_id) noexcept;

  friend class type_id_hash;

  template <typename T>
  friend constexpr type_id static_type_id() noexcept;
  friend constexpr type_id dynamic_type_id(std::string_view) noexcept;
};

class type_id_hash {
 public:
  constexpr size_t operator()(type_id id) const noexcept { return id.value_; }
};

}  // namespace volt

/*****************************************************************************
 * Inline implementations below this line
 *****************************************************************************/
namespace volt {

constexpr type_id::type_id() noexcept : value_{} {}

constexpr type_id::type_id(rep_t val) noexcept : value_{val} {}

constexpr type_id dynamic_type_id(std::string_view str_id) noexcept {
  // FNV-1a hash
  constexpr size_t offset_basis = 0xcbf29ce484222325;
  constexpr size_t prime = 0x100000001b3;

  size_t hash = offset_basis;

  for (auto& elem : str_id) {
    hash *= prime;
    hash |= elem;
  }

  return type_id{hash};
}

template <typename T>
constexpr type_id static_type_id() noexcept {
  return dynamic_type_id(type_name<T>());
}

constexpr bool operator==(type_id lhs, type_id rhs) noexcept {
  return lhs.value_ == rhs.value_;
}
constexpr bool operator!=(type_id lhs, type_id rhs) noexcept {
  return lhs.value_ != rhs.value_;
}
constexpr bool operator<=(type_id lhs, type_id rhs) noexcept {
  return lhs.value_ <= rhs.value_;
}
constexpr bool operator<(type_id lhs, type_id rhs) noexcept {
  return lhs.value_ < rhs.value_;
}
constexpr bool operator>=(type_id lhs, type_id rhs) noexcept {
  return lhs.value_ >= rhs.value_;
}
constexpr bool operator>(type_id lhs, type_id rhs) noexcept {
  return lhs.value_ > rhs.value_;
}
}  // namespace volt

#endif  // VOLT_TYPE_ID_HPP_
