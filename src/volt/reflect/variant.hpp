//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//

#ifndef VOLT_VARIANT_HPP_
#define VOLT_VARIANT_HPP_

#include "../containers/stl.hpp"
#include "../meta/concepts.hpp"
#include "type_id.hpp"

namespace volt::reflect {
class type_meta;

class variant {
 public:
  variant() noexcept = default;
  template <class T>
  variant(T&& obj) requires not_same_as<std::decay_t<T>, variant>;
  variant(const variant&);
  variant(variant&&) noexcept = default;
  variant& operator=(const variant&);
  variant& operator=(variant&&) noexcept = default;
  ~variant() noexcept = default;

  template <class T>
  T* get_if() const;
  type_id id() const noexcept;

  template <class T>
  bool is() const noexcept;
  bool contains_value() const noexcept;
  bool contains_reference() const noexcept;
  bool contains_const() const noexcept;
  bool valid() const noexcept;
  explicit operator bool() const noexcept;

 private:
  struct BaseData;
  template <class T>
  struct DerivedData;

  unique_ptr<BaseData> data_{};
};
}  // namespace volt::reflect

/*****************************************************************************
 * Inline implementations below this line
 *****************************************************************************/

namespace volt::reflect {

struct variant::BaseData {
  BaseData() noexcept = default;
  BaseData(const BaseData&) noexcept = default;
  BaseData(BaseData&&) noexcept = default;
  BaseData& operator=(const BaseData&) noexcept = default;
  BaseData& operator=(BaseData&&) noexcept = default;
  virtual ~BaseData() noexcept = default;

  virtual unique_ptr<BaseData> clone() const = 0;
  virtual void* get_data() noexcept = 0;
  virtual const void* get_const_data() const noexcept = 0;
  virtual bool is_ref() const noexcept = 0;
  virtual bool is_const() const noexcept = 0;
  virtual type_id id() const noexcept = 0;
};

template <class T>
struct variant::DerivedData : BaseData {
  T obj_;

  DerivedData() = default;
  explicit DerivedData(T&& obj) noexcept(noexcept(T(std::forward<T>(obj))))
      : obj_{std::forward<T>(obj)} {};
  DerivedData(const DerivedData&) = default;
  DerivedData(DerivedData&&) = delete;
  DerivedData& operator=(const DerivedData&) = delete;
  DerivedData& operator=(DerivedData&&) = delete;
  ~DerivedData() noexcept = default;

  unique_ptr<BaseData> clone() const override {
    return std::make_unique<DerivedData>(*this);
  }

  void* get_data() noexcept override {
    if constexpr (std::is_const_v<std::remove_reference_t<T>>) {
      return nullptr;
    } else {
      return std::addressof(obj_);
    }
  }

  const void* get_const_data() const noexcept override {
    return std::addressof(obj_);
  }
  bool is_ref() const noexcept override { return std::is_reference_v<T>; }
  bool is_const() const noexcept override {
    return std::is_const_v<std::remove_reference_t<T>>;
  }
  type_id id() const noexcept override {
    return static_type_id<std::decay_t<T>>();
  }
};

template <class T>
variant::variant(T&& obj) requires not_same_as<std::decay_t<T>, variant>
    : data_{std::make_unique<DerivedData<T>>(std::forward<T>(obj))} {}

template <class T>
T* variant::get_if() const {
  if (!this->is<T>()) {
    return nullptr;
  }

  if constexpr (std::is_const_v<T>) {
    return static_cast<T*>(data_->get_const_data());
  } else {
    return static_cast<T*>(data_->get_data());
  }
}

template <class T>
bool variant::is() const noexcept {
  if (!data_) {
    return false;
  }

  bool retval = true;
  // type check
  retval &= data_->id() == static_type_id<std::decay_t<T>>();
  if constexpr (std::is_const_v<std::remove_reference_t<T>>) {
    retval &= data_->is_const();
  }
  if constexpr (std::is_reference_v<T>) {
    retval &= data_->is_ref();
  }
  return retval;
}

}  // namespace volt::reflect

#endif  // VOLT_VARIANT_HPP_
