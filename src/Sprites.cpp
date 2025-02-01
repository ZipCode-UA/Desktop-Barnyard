#include "Sprites.h"
#include <iostream>

using namespace Gdiplus;

Sprites::Sprites():
    pBitmap(NULL),
    pSourceBitmap(NULL),
    pRenderTarget(NULL),
    velocity({3, 3}),
    pos({100, 100}),
    size({128, 128}),
    monitorSize({GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)})
{
}

Sprites::~Sprites() {
    if (m_hwnd){
        DestroyWindow(m_hwnd);
    }
}

void Sprites::timerUp() {
    std::cerr << "test\n";
    pos.x += velocity.x;
    pos.y += velocity.y;
    if (pos.x+size.x >= monitorSize.x || pos.x <= 0) velocity.x *= -1;
    if (pos.y + size.y >= monitorSize.y || pos.y <= 0) velocity.y *= -1;
    SetWindowPos(m_hwnd, HWND_TOPMOST, pos.x, pos.y, 100, 100, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOACTIVATE);
    SetTimer(Window(), 1001, 10, NULL);
    OnPaint(m_hwnd);
}

HRESULT Sprites::initialize(ID2D1Factory* pD2D1Factory, IWICImagingFactory* pWICFactory){
    
    this->pWICFactory = pWICFactory;
    this->pD2D1Factory = pD2D1Factory;

    HRESULT hr = S_OK;
    if(SUCCEEDED(hr)){
        // Create window
        if (!Create(L"TestSprite", 
            WS_POPUP | WS_VISIBLE, // popup means no boarder
            WS_EX_LAYERED, // only transparent window style
            pos.x, pos.y, // starting position
            size.x, size.y // size
        )) {
            throw std::runtime_error("Failed to create sprite window");
        }

        SetLayeredWindowAttributes(m_hwnd, RGB(255, 255, 255), 0, LWA_COLORKEY); // sets whites to be transparent
        
        SetWindowPos(m_hwnd, HWND_TOPMOST, pos.x, pos.y, size.x, size.y, SWP_SHOWWINDOW);
        SetTimer(Window(), 1001, 10, NULL);
    }

    hr = makeBitmap();

    return S_OK;
}

HRESULT Sprites::makeBitmap(){
    HRESULT hr = S_OK;

    WCHAR szFileName[MAX_PATH];

    // Step 1: Create the open dialog box and locate the image file
    if (locateImageFile(szFileName, ARRAYSIZE(szFileName)))
    {
        // Step 2: Decode the source image

        // Create a decoder
        IWICBitmapDecoder *pDecoder = NULL;

        hr = pWICFactory->CreateDecoderFromFilename(
            szFileName,                      // Image to be decoded
            NULL,                            // Do not prefer a particular vendor
            GENERIC_READ,                    // Desired read access to the file
            WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
            &pDecoder                        // Pointer to the decoder
            );

        // Retrieve the first frame of the image from the decoder
        IWICBitmapFrameDecode *pFrame = NULL;

        if (SUCCEEDED(hr))
        {
            hr = pDecoder->GetFrame(0, &pFrame);
        }

        //Step 3: Format convert the frame to 32bppPBGRA
        if (SUCCEEDED(hr))
        {
            SafeRelease(&pSourceBitmap);
            hr = pWICFactory->CreateFormatConverter(&pSourceBitmap);
        }

        if (SUCCEEDED(hr))
        {
            hr = pSourceBitmap->Initialize(
                pFrame,                          // Input bitmap to convert
                GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
                WICBitmapDitherTypeNone,         // Specified dither pattern
                NULL,                            // Specify a particular palette 
                0.f,                             // Alpha threshold
                WICBitmapPaletteTypeCustom       // Palette translation type
                );
        }

        //Step 4: Create render target and D2D bitmap from IWICBitmapSource
        if (SUCCEEDED(hr))
        {
            hr = CreateDeviceResources();
        }


        if (SUCCEEDED(hr))
        {
            // Need to release the previous D2DBitmap if there is one
            SafeRelease(&pBitmap);
            hr = pRenderTarget->CreateBitmapFromWicBitmap(pSourceBitmap, NULL, &pBitmap);
        }

        SafeRelease(&pDecoder);
        SafeRelease(&pFrame);
    }

    return hr;
}

HRESULT Sprites::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    if (!pRenderTarget)
    {
        RECT rc;
        hr = GetClientRect(m_hwnd, &rc) ? S_OK : E_FAIL;

        if (SUCCEEDED(hr))
        {
            // Create a D2D render target properties
            D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties();

            // Set the DPI to be the default system DPI to allow direct mapping
            // between image pixels and desktop pixels in different system DPI settings
            renderTargetProperties.dpiX = DEFAULT_DPI;
            renderTargetProperties.dpiY = DEFAULT_DPI;

            // Create a D2D render target
            D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

            hr = pD2D1Factory->CreateHwndRenderTarget(
                renderTargetProperties,
                D2D1::HwndRenderTargetProperties(m_hwnd, size),
                &pRenderTarget
                );
        }
    }

    return hr;
}

BOOL Sprites::locateImageFile(LPWSTR pszFileName, DWORD cchFileName)
{
    pszFileName[0] = L'\0';

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = m_hwnd;
    ofn.lpstrFilter     = L"All Image Files\0"              L"*.bmp;*.dib;*.wdp;*.mdp;*.hdp;*.gif;*.png;*.jpg;*.jpeg;*.tif;*.ico\0"
                          L"Windows Bitmap\0"               L"*.bmp;*.dib\0"
                          L"High Definition Photo\0"        L"*.wdp;*.mdp;*.hdp\0"
                          L"Graphics Interchange Format\0"  L"*.gif\0"
                          L"Portable Network Graphics\0"    L"*.png\0"
                          L"JPEG File Interchange Format\0" L"*.jpg;*.jpeg\0"
                          L"Tiff File\0"                    L"*.tif\0"
                          L"Icon\0"                         L"*.ico\0"
                          L"All Files\0"                    L"*.*\0"
                          L"\0";
    ofn.lpstrFile       = pszFileName;
    ofn.nMaxFile        = cchFileName;
    ofn.lpstrTitle      = L"Open Image";
    ofn.Flags           = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    // Display the Open dialog box. 
    return GetOpenFileName(&ofn);
}

LRESULT Sprites::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg)
    {
    case WM_DESTROY:
        return 0;
    case WM_QUIT:
        return 0;
    case WM_TIMER:
        timerUp();
        return 0;
    case WM_PAINT:
        OnPaint(m_hwnd);
        return 0;
    default:
        break;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam); 
}

LRESULT Sprites::OnPaint(HWND hWnd){
    HRESULT hr = S_OK;
    PAINTSTRUCT ps;

    if (BeginPaint(hWnd, &ps))
    {
        // Create render target if not yet created
        hr = CreateDeviceResources();

        if (SUCCEEDED(hr) && !(pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
        {
            pRenderTarget->BeginDraw();

            pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

            // Clear the background
            pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

            D2D1_SIZE_F rtSize = pRenderTarget->GetSize();

            // Create a rectangle same size of current window
            D2D1_RECT_F rectangle = D2D1::RectF(0.0f, 0.0f, rtSize.width, rtSize.height);

            // D2DBitmap may have been released due to device loss. 
            // If so, re-create it from the source bitmap
            if (pSourceBitmap && !pBitmap)
            {
                pRenderTarget->CreateBitmapFromWicBitmap(pSourceBitmap, NULL, &pBitmap);
            }

            // Draws an image and scales it to the current window size
            if (pBitmap)
            {
                pRenderTarget->DrawBitmap(pBitmap, rectangle);
            }

            hr = pRenderTarget->EndDraw();

            // In case of device loss, discard D2D render target and D2DBitmap
            // They will be re-create in the next rendering pass
            if (hr == D2DERR_RECREATE_TARGET)
            {
                pRenderTarget->EndDraw();
                SafeRelease(&pBitmap);
                SafeRelease(&pRenderTarget);
                // Force a re-render
                hr = InvalidateRect(hWnd, NULL, TRUE)? S_OK : E_FAIL;
            }
        }

        EndPaint(hWnd, &ps);
    }

    return SUCCEEDED(hr) ? 0 : 1;
}