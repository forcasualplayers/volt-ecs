//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//

#ifndef VOLT_TYPE_NAME_HPP_
#define VOLT_TYPE_NAME_HPP_

#include <string_view>

namespace volt {
template <typename T>
constexpr std::string_view type_name() noexcept;
}  // namespace volt

/*****************************************************************************
 * Inline implementations below this line
 *****************************************************************************/

#if defined(__clang_major__)
#define VOLT_FUNCNAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define VOLT_FUNCNAME __FUNCSIG__
#elif defined(__GNUC__)
#define VOLT_FUNCNAME __PRETTY_FUNCTION__
#endif

namespace volt {
namespace reflect_detail {
template <typename T>
constexpr std::string_view get_name(unsigned& offset, unsigned& end) noexcept;

template <>
constexpr std::string_view get_name<float>(unsigned& offset,
                                           unsigned& end) noexcept {
  std::string_view raw_str = VOLT_FUNCNAME;
  offset = raw_str.find("float");
  end = raw_str.length() - offset - 5;
  return "float";
}

template <typename T>
constexpr std::string_view get_name(unsigned&, unsigned&) noexcept {
  unsigned offset{};
  unsigned end{};
  get_name<float>(offset, end);

  std::string_view raw_str = VOLT_FUNCNAME;

  auto retval = raw_str.substr(offset);
  retval.remove_suffix(end);
  return retval;
}
}  // namespace reflect_detail

template <typename T>
constexpr std::string_view type_name() noexcept {
  unsigned offset{};
  unsigned end{};
  return reflect_detail::get_name<T>(offset, end);
}
}  // namespace volt

#undef VOLT_FUNCNAME

#endif  // VOLT_TYPE_NAME_HPP_
