//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//

#ifndef VOLT_PROPERTY_HPP_
#define VOLT_PROPERTY_HPP_

#include "../containers/stl.hpp"
#include "type_id.hpp"

namespace volt::reflect {
class variant;

class property {
 public:
  template <class GetterFunc, class SetterFunc>
  property(string_view prop_name, GetterFunc getter, SetterFunc setter);
  template <class FieldT, class ObjT>
  property(string_view prop_name, FieldT(ObjT::*mem_ptr));

  string_view name() const noexcept;
  type_id type() const noexcept;
  type_id declaring_type() const noexcept;

  variant get_value(const variant& obj) const;
  void set_value(const variant& obj, const variant& value) const;

 private:
  using GetterT = function<variant(const variant& obj)>;
  using SetterT = function<void(const variant& obj, const variant& value)>;
  string name_;
  type_id obj_type_;
  type_id field_type_;
  GetterT getter_;
  SetterT setter_;
};
}  // namespace volt::reflect

/*****************************************************************************
 * Inline implementations below this line
 *****************************************************************************/
#include "variant.hpp"

namespace volt::reflect {
template <class FieldT, class ObjT>
property::property(string_view prop_name, FieldT(ObjT::*mem_ptr))
    : name_{prop_name},
      obj_type_{static_type_id<ObjT>()},
      field_type_{static_type_id<FieldT>()},
      getter_{[mem_ptr](const variant& obj) -> variant {
        if (auto unwrapped_obj = obj.get_if<ObjT>()) {
          return volt::reflect::variant{FieldT{unwrapped_obj->*mem_ptr}};
        }
        return volt::reflect::variant{};
      }},
      setter_{[mem_ptr](const variant& obj, const variant& val) -> void {
        if (auto unwrapped_obj = obj.get_if<ObjT>()) {
          if (auto unwrapped_val = val.get_if<FieldT>()) {
            unwrapped_obj->*mem_ptr = *unwrapped_val;
          }
        }
      }} {}
}  // namespace volt::reflect
#endif  // VOLT_PROPERTY_HPP_
