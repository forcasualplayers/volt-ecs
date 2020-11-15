//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//

#include "type_meta.hpp"

namespace volt::reflect {
type_meta::type_meta(string_view name, type_id id, size_t sz)
    : name_{name}, id_{id}, size_{sz} {}

type_meta::type_meta(const type_meta&) = default;
type_meta::type_meta(type_meta&&) noexcept = default;
type_meta::~type_meta() noexcept = default;
type_meta& type_meta::operator=(const type_meta&) = default;
type_meta& type_meta::operator=(type_meta&&) noexcept = default;

[[nodiscard]] string_view type_meta::name() const noexcept { return name_; }
[[nodiscard]] type_id type_meta::id() const noexcept { return id_; }
[[nodiscard]] size_t type_meta::size() const noexcept { return size_; }

}  // namespace volt::reflect