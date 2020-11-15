//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//

#include "type_meta.hpp"

#include "property.hpp"

namespace volt::reflect {
type_meta::type_meta(string_view name, type_id id, size_t align, size_t sz)
    : name_{name}, id_{id}, align_{align}, size_{sz} {}

type_meta::type_meta(const type_meta&) = default;
type_meta::type_meta(type_meta&&) noexcept = default;
type_meta::~type_meta() noexcept = default;
type_meta& type_meta::operator=(const type_meta&) = default;
type_meta& type_meta::operator=(type_meta&&) noexcept = default;

[[nodiscard]] size_t type_meta::align() const noexcept { return align_; }
[[nodiscard]] string_view type_meta::name() const noexcept { return name_; }
[[nodiscard]] type_id type_meta::id() const noexcept { return id_; }
[[nodiscard]] size_t type_meta::size() const noexcept { return size_; }

span<const property> type_meta::properties() const noexcept {
  return span{properties_};
}

void type_meta::register_property(const property& ppt) {
  properties_.emplace_back(ppt);
}

}  // namespace volt::reflect