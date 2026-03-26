// SPDX-License-Identifier: MIT
#pragma once

#include "Core/BinaryDocument.h"

#include <cstddef>

namespace BinXray::UI {

class InspectorPanel {
public:
    void draw(const Core::BinaryDocument& document, std::size_t selectedOffset) const;
};

} // namespace BinXray::UI
