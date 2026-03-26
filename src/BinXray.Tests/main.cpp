// SPDX-License-Identifier: MIT

#include <iostream>

bool runByteFormatterTests();
bool runBinaryDocumentTests();
bool runTransitionMatrixTests();

int main() {
    int failedSuites = 0;

    if (!runByteFormatterTests()) {
        ++failedSuites;
    }

    if (!runBinaryDocumentTests()) {
        ++failedSuites;
    }

    if (!runTransitionMatrixTests()) {
        ++failedSuites;
    }

    if (failedSuites == 0) {
        std::cout << "All BinXray tests passed." << std::endl;
        return 0;
    }

    std::cout << failedSuites << " test suite(s) failed." << std::endl;
    return 1;
}
