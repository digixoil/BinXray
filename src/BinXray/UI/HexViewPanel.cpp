// SPDX-License-Identifier: MIT

#include "HexViewPanel.h"

#include "Core/ByteFormatter.h"
#include "imgui.h"

#include <algorithm>
#include <string>

namespace BinXray::UI {

void HexViewPanel::draw(const Core::BinaryDocument& document, std::size_t& selectedOffset) const {
    ImGui::Begin("Hex View");
    drawContent(document, selectedOffset, 0, document.bytes().size());
    ImGui::End();
}

void HexViewPanel::drawEmbedded(const Core::BinaryDocument& document,
                                std::size_t& selectedOffset,
                                std::size_t rangeStartInclusive,
                                std::size_t rangeEndExclusive) const {
    drawContent(document, selectedOffset, rangeStartInclusive, rangeEndExclusive);
}

void HexViewPanel::drawContent(const Core::BinaryDocument& document,
                               std::size_t& selectedOffset,
                               std::size_t rangeStartInclusive,
                               std::size_t rangeEndExclusive) const {
    const auto& bytes = document.bytes();
    if (bytes.empty()) {
        ImGui::TextUnformatted("No binary data loaded.");
        return;
    }

    const std::size_t clampedStart = std::min(rangeStartInclusive, bytes.size());
    const std::size_t clampedEnd = std::min(rangeEndExclusive, bytes.size());
    const std::size_t rangeStart = std::min(clampedStart, clampedEnd);
    const std::size_t rangeEnd = std::max(clampedStart, clampedEnd);
    const std::size_t rangeLength = rangeEnd - rangeStart;
    if (rangeLength == 0) {
        ImGui::TextUnformatted("Selected range is empty.");
        return;
    }

    const std::size_t bytesPerRow = 16;
    const std::size_t maxVisibleBytes = std::min(rangeLength, static_cast<std::size_t>(4096));

    ImGui::BeginChild("HexViewScrollRegion");

    for (std::size_t relativeOffset = 0; relativeOffset < maxVisibleBytes; relativeOffset += bytesPerRow) {
        const std::size_t absoluteOffset = rangeStart + relativeOffset;
        const std::string offsetLabel = Core::formatOffsetHex(absoluteOffset);
        ImGui::TextUnformatted(offsetLabel.c_str());
        ImGui::SameLine();

        for (std::size_t column = 0; column < bytesPerRow && (relativeOffset + column) < maxVisibleBytes; ++column) {
            const std::size_t index = absoluteOffset + column;
            const std::string valueLabel = Core::formatByteHex(bytes[index]);
            const std::string buttonId = valueLabel + "##byte_" + std::to_string(index);

            if (index == selectedOffset) {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(55, 120, 220, 255));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(75, 140, 240, 255));
            }

            if (ImGui::SmallButton(buttonId.c_str())) {
                selectedOffset = index;
            }

            if (index == selectedOffset) {
                ImGui::PopStyleColor(2);
            }

            if (column + 1 < bytesPerRow && (relativeOffset + column + 1) < maxVisibleBytes) {
                ImGui::SameLine();
            }
        }
    }

    if (rangeLength > maxVisibleBytes) {
        ImGui::Separator();
        ImGui::Text("Showing first %zu bytes of selected %zu-byte range.", maxVisibleBytes, rangeLength);
    }

    ImGui::EndChild();
}

} // namespace BinXray::UI
