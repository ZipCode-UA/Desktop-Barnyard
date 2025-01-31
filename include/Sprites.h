#ifndef SPRITES_H
#define SPRITES_H

#include "BaseWindow.h"

#include <d2d1.h>
#include <d2d1helper.h>
#include <wincodec.h>
#include <windows.h>
#include <gdiplus.h>
#include <commdlg.h>

#include <filesystem>

// We wil probably need windows animation in the future
// https://learn.microsoft.com/en-us/windows/win32/uianimation/windows-animation-developer-guide
// It uses the COM library

class Sprites : public BaseWindow<Sprites> {
    const FLOAT DEFAULT_DPI = 96.f;

    // Direct2D stuff 
    ID2D1Factory*           pD2D1Factory;
    ID2D1HwndRenderTarget*  pRenderTarget;
    ID2D1Bitmap*            pBitmap;
    IWICImagingFactory*     pWICFactory; // WIC is windows imaging compnent
    IWICFormatConverter*    pSourceBitmap;
    Gdiplus::Bitmap*        pGdiPlusBitmap;

public:
    // Windows stuff
    HRESULT initialize();
    PCWSTR ClassName() const override { return L"Sprite"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    HRESULT CreateDeviceResources();
    LRESULT OnPaint(HWND hWnd);

    Sprites();
    ~Sprites();

    HRESULT makeBitmap();
    BOOL locateImageFile(LPWSTR pszFileName, DWORD cchFileName);

    void showSprite();
    void timerUp();
    
    POINT pos;
    POINT velocity;
    POINT size;
    POINT monitorSize;

};

#endif