// SPDX-License-Identifier: MIT
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace BinXray::Core {

class TransitionMatrix {
public:
    static constexpr std::size_t kDimension = 256;
    static constexpr std::size_t kCellCount = kDimension * kDimension;

    enum class RenderMode {
        Binary,
        Linear,
        Normalized
    };

    using Counts = std::array<std::uint32_t, kCellCount>;
    using Luminance = std::array<std::uint8_t, kCellCount>;

    TransitionMatrix();

    void compute(const std::vector<std::uint8_t>& bytes, std::size_t startOffsetInclusive, std::size_t endOffsetExclusive);
    [[nodiscard]] std::uint32_t count(std::uint8_t from, std::uint8_t to) const noexcept;
    [[nodiscard]] std::uint32_t maxCount() const noexcept;
    [[nodiscard]] std::size_t startOffset() const noexcept;
    [[nodiscard]] std::size_t endOffset() const noexcept;

    [[nodiscard]] const Counts& counts() const noexcept;
    void renderLuminance(RenderMode mode, Luminance& output) const;
    [[nodiscard]] Luminance renderLuminance(RenderMode mode) const;

private:
    static std::size_t toIndex(std::uint8_t from, std::uint8_t to) noexcept;
    static std::uint8_t mapIntensity(std::uint32_t density, RenderMode mode) noexcept;

    Counts m_counts;
    std::size_t m_startOffset;
    std::size_t m_endOffset;
    std::uint32_t m_maxCount;
};

} // namespace BinXray::Core
