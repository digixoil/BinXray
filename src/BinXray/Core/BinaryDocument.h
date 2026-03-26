// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace BinXray::Core {

struct BinaryLoadResult {
    bool success;
    std::vector<std::uint8_t> bytes;
    std::wstring path;
    std::wstring error;
};

class BinaryDocument {
public:
    [[nodiscard]] static BinaryLoadResult loadFileBytes(const std::wstring& path);

    [[nodiscard]] bool loadFromFile(const std::wstring& path);
    void replace(std::vector<std::uint8_t>&& bytes, std::wstring&& path);
    void loadSampleData();

    [[nodiscard]] const std::vector<std::uint8_t>& bytes() const noexcept;
    [[nodiscard]] const std::wstring& sourcePath() const noexcept;

private:
    std::vector<std::uint8_t> m_bytes;
    std::wstring m_sourcePath;
};

} // namespace BinXray::Core
