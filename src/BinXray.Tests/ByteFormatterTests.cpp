// SPDX-License-Identifier: MIT

#include "Core/ByteFormatter.h"

#include <iostream>

namespace {

bool expectEqual(const std::string& actual, const std::string& expected, const char* caseName) {
    if (actual == expected) {
        return true;
    }

    std::cout << "[FAIL] " << caseName << " expected='" << expected << "' actual='" << actual << "'" << std::endl;
    return false;
}

} // namespace

bool runByteFormatterTests() {
    bool passed = true;

    passed = expectEqual(BinXray::Core::formatByteHex(0x00), "00", "formatByteHex(0x00)") && passed;
    passed = expectEqual(BinXray::Core::formatByteHex(0xAF), "AF", "formatByteHex(0xAF)") && passed;
    passed = expectEqual(BinXray::Core::formatOffsetHex(0), "0x00000000", "formatOffsetHex(0)") && passed;
    passed = expectEqual(BinXray::Core::formatOffsetHex(4096), "0x00001000", "formatOffsetHex(4096)") && passed;

    if (passed) {
        std::cout << "[PASS] ByteFormatterTests" << std::endl;
    }

    return passed;
}
