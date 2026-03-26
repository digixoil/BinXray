// SPDX-License-Identifier: MIT
#pragma once

#include "Core/BinaryDocument.h"

#include <string>

namespace BinXray::UI {

class StatusBar {
public:
    void draw(const Core::BinaryDocument& document,
              bool isLoadingFile,
              const std::wstring& loadingPath,
              const std::wstring& lastLoadError) const;
};

} // namespace BinXray::UI
