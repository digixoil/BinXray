// SPDX-License-Identifier: MIT
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace BinXray::Core {

[[nodiscard]] std::string formatByteHex(std::uint8_t value);
[[nodiscard]] std::string formatOffsetHex(std::size_t offset);

} // namespace BinXray::Core
