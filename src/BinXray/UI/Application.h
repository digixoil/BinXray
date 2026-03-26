// SPDX-License-Identifier: MIT
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

#include "Core/BinaryDocument.h"
#include "Core/TransitionMatrix.h"
#include "UI/HexViewPanel.h"

#include <future>
#include <optional>
#include <string>

namespace BinXray::UI {

class Application {
public:
    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    bool initialize(HINSTANCE hInstance);
    int run();
    void shutdown();

private:
    struct AsyncLoadResult {
        bool success;
        std::vector<std::uint8_t> bytes;
        std::wstring sourcePath;
        std::wstring error;
    };

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT handleWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    [[nodiscard]] std::optional<std::wstring> promptOpenFilePath() const;
    void startAsyncFileLoad(const std::wstring& path);
    void pollAsyncFileLoad();
    void refreshRangeAfterDocumentChange();
    void setWindowFromCenter(std::size_t centerOffset);
    void rebuildMatrixIfDirty();
    void drawWorkspace();
    void drawControlsColumn();
    void drawCenterColumn();
    void drawMatrixPlot(float heightPixels);
    void drawRibbonColumn();

    bool createDeviceD3D(HWND hWnd);
    void cleanupDeviceD3D();
    void createRenderTarget();
    void cleanupRenderTarget();
    void renderFrame();

    HINSTANCE m_hInstance;
    HWND m_hWnd;
    bool m_running;
    bool m_initialized;

    IDXGISwapChain* m_swapChain;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    ID3D11RenderTargetView* m_mainRenderTargetView;

    Core::BinaryDocument m_document;
    std::size_t m_selectedOffset;
    Core::TransitionMatrix m_transitionMatrix;
    Core::TransitionMatrix::Luminance m_matrixLuminance;

    bool m_scaleEnabled;
    bool m_normalizeEnabled;
    bool m_fullViewEnabled;
    int m_blockSize;
    std::size_t m_windowStartOffset;
    std::size_t m_windowEndOffset;
    bool m_matrixDirty;

    bool m_isLoadingFile;
    std::future<AsyncLoadResult> m_asyncLoadFuture;
    std::wstring m_loadingPath;
    std::wstring m_lastLoadError;

    HexViewPanel m_hexViewPanel;
};

} // namespace BinXray::UI
