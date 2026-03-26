// SPDX-License-Identifier: MIT

#include "BinaryDocument.h"

#include <cstring>
#include <fstream>
#include <utility>
#include <vector>

namespace BinXray::Core {

BinaryLoadResult BinaryDocument::loadFileBytes(const std::wstring& path) {
    BinaryLoadResult result = {};
    result.success = false;
    result.path = path;

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        result.error = L"Unable to open file for reading.";
        return result;
    }

    file.seekg(0, std::ios::end);
    const std::streamoff fileSize = file.tellg();
    if (fileSize > 0) {
        result.bytes.reserve(static_cast<std::size_t>(fileSize));
    }
    file.seekg(0, std::ios::beg);

    constexpr std::size_t chunkSize = 1024 * 1024;
    std::vector<char> buffer(chunkSize);

    while (file) {
        file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        const std::streamsize bytesRead = file.gcount();
        if (bytesRead <= 0) {
            break;
        }

        const std::size_t currentSize = result.bytes.size();
        const std::size_t newSize = currentSize + static_cast<std::size_t>(bytesRead);
        result.bytes.resize(newSize);
        std::memcpy(result.bytes.data() + currentSize, buffer.data(), static_cast<std::size_t>(bytesRead));
    }

    if (file.bad()) {
        result.bytes.clear();
        result.error = L"I/O error while reading file.";
        return result;
    }

    result.success = true;
    return result;
}

bool BinaryDocument::loadFromFile(const std::wstring& path) {
    BinaryLoadResult result = loadFileBytes(path);
    if (!result.success) {
        return false;
    }

    replace(std::move(result.bytes), std::move(result.path));
    return true;
}

void BinaryDocument::replace(std::vector<std::uint8_t>&& bytes, std::wstring&& path) {
    m_bytes = std::move(bytes);
    m_sourcePath = std::move(path);
}

void BinaryDocument::loadSampleData() {
    m_sourcePath.clear();
    m_bytes.resize(1024);
    for (std::size_t i = 0; i < m_bytes.size(); ++i) {
        m_bytes[i] = static_cast<std::uint8_t>(i % 256);
    }
}

const std::vector<std::uint8_t>& BinaryDocument::bytes() const noexcept {
    return m_bytes;
}

const std::wstring& BinaryDocument::sourcePath() const noexcept {
    return m_sourcePath;
}

} // namespace BinXray::Core
