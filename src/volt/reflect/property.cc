//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//

#include "property.hpp"

namespace volt::reflect {

string_view property::name() const noexcept { return name_; }

type_id property::type() const noexcept { return field_type_; }

type_id property::declaring_type() const noexcept { return obj_type_; }

variant property::get_value(const variant& obj) const { return getter_(obj); }

void property::set_value(const variant& obj, const variant& value) const {
  setter_(obj, value);
}

}  // namespace volt::reflect