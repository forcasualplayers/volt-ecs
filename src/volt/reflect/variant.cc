//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//

#include "variant.hpp"

#include "property.hpp"

namespace volt::reflect {
variant::variant(const variant& rhs)
    : data_{rhs.data_ ? rhs.data_->clone() : nullptr} {}

variant& variant::operator=(const variant& rhs) {
  auto copy = rhs.data_->clone();
  data_ = std::move(copy);
  return *this;
}

type_id variant::id() const noexcept { return data_ ? data_->id() : type_id{}; }

bool variant::contains_value() const noexcept {
  return data_ ? !data_->is_ref() : false;
}

bool variant::contains_reference() const noexcept {
  return data_ ? data_->is_ref() : false;
}

bool variant::contains_const() const noexcept {
  return data_ ? data_->is_const() : false;
}

bool variant::valid() const noexcept { return bool{data_}; }

variant::operator bool() const noexcept { return valid(); }
}  // namespace volt::reflect