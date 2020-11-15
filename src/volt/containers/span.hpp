//
// Copyright (c) 2020 Ho Han Kit Ivan
// Licensed under the MIT license. See LICENSE file in the project root for
// details.
//

#ifndef VOLT_SPAN_HPP_
#define VOLT_SPAN_HPP_

#if __cplusplus > 201703L
#include <span>

namespace volt {
using std::span;
}
#else   // __cplusplus > 201703L
static_assert(false, "Span unavailable");
#endif  // __cplusplus > 201703L

#endif  // VOLT_SPAN_HPP_
