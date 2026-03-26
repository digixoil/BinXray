// SPDX-License-Identifier: MIT
#pragma once

#include "Core/BinaryDocument.h"

#include <cstddef>

namespace BinXray::UI {

class HexViewPanel {
public:
    void draw(const Core::BinaryDocument& document, std::size_t& selectedOffset) const;
    void drawEmbedded(const Core::BinaryDocument& document,
                      std::size_t& selectedOffset,
                      std::size_t rangeStartInclusive,
                      std::size_t rangeEndExclusive) const;

private:
    void drawContent(const Core::BinaryDocument& document,
                     std::size_t& selectedOffset,
                     std::size_t rangeStartInclusive,
                     std::size_t rangeEndExclusive) const;
};

} // namespace BinXray::UI
