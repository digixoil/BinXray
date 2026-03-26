// SPDX-License-Identifier: MIT

#include "StatusBar.h"

#include "UIConstants.h"
#include "imgui.h"

namespace BinXray::UI {

void StatusBar::draw(const Core::BinaryDocument& document,
                     bool isLoadingFile,
                     const std::wstring& loadingPath,
                     const std::wstring& lastLoadError) const {
    ImGui::Begin("Status");
    ImGui::Text("Bytes loaded: %zu", document.bytes().size());
    if (!document.sourcePath().empty()) {
        ImGui::Text("File: %ls", document.sourcePath().c_str());
    } else {
        ImGui::TextUnformatted("File: sample dataset");
    }

    if (isLoadingFile) {
        ImGui::Text("Load state: loading %ls", loadingPath.c_str());
    } else {
        ImGui::TextUnformatted("Load state: idle");
    }

    if (!lastLoadError.empty()) {
        ImGui::TextColored(Constants::kErrorTextColor, "Last load error: %ls", lastLoadError.c_str());
    }
    ImGui::End();
}

} // namespace BinXray::UI
