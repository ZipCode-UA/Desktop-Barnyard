#ifndef SPRITES_H
#define SPRITES_H

#include "BaseWindow.h"

#include <d2d1.h>
#include <wincodec.h>

#include <filesystem>


// We wil probably need windows animation in the future
// https://learn.microsoft.com/en-us/windows/win32/uianimation/windows-animation-developer-guide
// It uses the COM library
     

class Sprites : public BaseWindow<Sprites> {
    // Direct2D stuff 
    ID2D1Factory*           pFactory = nullptr;
    ID2D1HwndRenderTarget*  pRenderTarget = nullptr;
    ID2D1Bitmap*            pBitmap = nullptr;
    IWICImagingFactory*     pWICFactory = nullptr; // WIC is windows imaging compnent

    HRESULT CreateGraphicsResources();

public:
    // Windows stuff
    PCWSTR ClassName() const override { return L"Sprite"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Normal program stuff
    Sprites();
    
    // later we will probably want to make something that loads all assets into bitmaps when the program start
    const std::filesystem::path testImagePath = "../TestAsset.png";
    
    POINT position;

};

#endif