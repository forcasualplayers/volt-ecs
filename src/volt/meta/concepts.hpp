//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//
#ifndef VOLT_CONCEPTS_HPP_
#define VOLT_CONCEPTS_HPP_

#include <concepts>
#include <type_traits>

namespace volt {

template <class T, class U>
concept not_same_as = !std::is_same_v<T, U> || !std::is_same_v<U, T>;
}

#endif  // VOLT_CONCEPTS_HPP_
