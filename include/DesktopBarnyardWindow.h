#ifndef DESKTOPBARNYARDWINDOW_H
#define DESKTOPBARNYARDWINDOW_H

#include "BaseWindow.h"
#include "Sprites.h"

#include <vector>

class DesktopBarnyardWindow : public BaseWindow<DesktopBarnyardWindow> {

    void createButtons();
    HWND spawnCreatureButton = NULL;
    HWND despawnCreatureButton = NULL;

    Sprites testSprite;
    
public:
    DesktopBarnyardWindow();

    PCWSTR ClassName() const override { return L"Barnyard"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};



#endif