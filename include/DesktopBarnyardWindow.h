#ifndef DESKTOPBARNYARDWINDOW_H
#define DESKTOPBARNYARDWINDOW_H

#include "BaseWindow.h"
#include "Sprites.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <wincodec.h>
#include <windows.h>
#include <gdiplus.h>
#include <commdlg.h>

#include <vector>

class DesktopBarnyardWindow : public BaseWindow<DesktopBarnyardWindow> {

    // Object factories that we pass to the sprites so they create graphics resources
    IWICImagingFactory*     pWICFactory; // WIC is windows imaging compnent
    ID2D1Factory*   pD2D1Factory;

    void createButtons();
    HWND spawnCreatureButton = NULL;
    HWND despawnCreatureButton = NULL;

    void despawnCreature();
    void spawnCreature();

    std::vector<Sprites*> SpriteList;
    
public:
    DesktopBarnyardWindow();

    PCWSTR ClassName() const override { return L"Barnyard"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};



#endif