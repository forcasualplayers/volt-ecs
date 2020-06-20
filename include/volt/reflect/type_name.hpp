//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//

#ifndef VOLT_TYPE_NAME_HPP_
#define VOLT_TYPE_NAME_HPP_

#include <string_view>
#include <utility>

namespace volt {
template <typename T>
constexpr std::string_view type_name() noexcept;
}  // namespace volt

/*****************************************************************************
 * Inline implementations below this line
 *****************************************************************************/

#if defined(_MSC_VER)
#define VOLT_FUNCNAME __FUNCSIG__
#elif defined(__clang_major__)
#define VOLT_FUNCNAME __PRETTY_FUNCTION__
#elif defined(__GNUC__)
#define VOLT_FUNCNAME __PRETTY_FUNCTION__
#endif

#define VOLT_FALLBACK_TYPE float
#define VOLT_XSTRINGIFY(STR) VOLT_STRINGIFY(STR)
#define VOLT_STRINGIFY(STR) #STR

namespace volt {
namespace reflect_detail {
template <typename T>
constexpr std::string_view get_name(unsigned& offset, unsigned& end) noexcept;

template <typename T>
constexpr std::string_view get_name(unsigned& offset, unsigned& end) noexcept {
  if constexpr (std::is_same_v<T, VOLT_FALLBACK_TYPE>) {
    std::string_view raw_str = VOLT_FUNCNAME;
    offset = static_cast<unsigned>(
        raw_str.find(VOLT_XSTRINGIFY(VOLT_FALLBACK_TYPE)));
    end = static_cast<unsigned>(
        raw_str.length() - offset -
        std::string_view(VOLT_XSTRINGIFY(VOLT_FALLBACK_TYPE)).length());
    return VOLT_XSTRINGIFY(VOLT_FALLBACK_TYPE);

  } else {
    get_name<VOLT_FALLBACK_TYPE>(offset, end);

    std::string_view retval = VOLT_FUNCNAME + offset;
    retval.remove_suffix(end);
    return retval;
  }
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
#undef VOLT_XSTRINGIFY
#undef VOLT_STRINGIFY

#endif  // VOLT_TYPE_NAME_HPP_
