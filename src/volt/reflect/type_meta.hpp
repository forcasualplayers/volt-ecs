//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//
#ifndef VOLT_TYPE_META_HPP_
#define VOLT_TYPE_META_HPP_

#include <string>
#include <string_view>

#include "../containers/stl.hpp"
#include "type_id.hpp"

namespace volt::reflect {

class property;
class constructor;

class type_meta {
 public:
  type_meta(string_view name, type_id id, size_t alignment, size_t sz);
  type_meta(const type_meta&);
  type_meta(type_meta&&) noexcept;
  ~type_meta() noexcept;
  type_meta& operator=(const type_meta&);
  type_meta& operator=(type_meta&&) noexcept;

  [[nodiscard]] size_t align() const noexcept;
  [[nodiscard]] type_id id() const noexcept;
  [[nodiscard]] string_view name() const noexcept;
  [[nodiscard]] size_t size() const noexcept;

  //[[nodiscard]] span<const constructor> constructors() const noexcept;
  [[nodiscard]] span<const property> properties() const noexcept;

  // void register_constructor(const constructor& ctor);
  void register_property(const property& ppt);
  // void register_parent(const type_id& parent);

 private:
  string name_{};
  type_id id_{};
  size_t size_{};
  size_t align_{};

  // vector<constructor> constructors_;
  vector<property> properties_;
};

}  // namespace volt::reflect

#endif  // VOLT_TYPE_META_HPP_
