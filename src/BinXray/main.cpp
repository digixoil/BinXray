// SPDX-License-Identifier: MIT
// main.cpp - Application entry point.

#include "UI/Application.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                    _In_opt_ HINSTANCE /*hPrevInstance*/,
                    _In_ LPWSTR /*lpCmdLine*/,
                    _In_ int /*nShowCmd*/) {
    BinXray::UI::Application app;

    if (!app.initialize(hInstance)) {
        ::MessageBoxW(
            nullptr,
            L"Failed to initialize BinXray.\n"
            L"Please verify Direct3D 11 support and try again.",
            L"BinXray Startup Error",
            MB_OK | MB_ICONERROR);
        return 1;
    }

    const int exitCode = app.run();
    app.shutdown();
    return exitCode;
}
