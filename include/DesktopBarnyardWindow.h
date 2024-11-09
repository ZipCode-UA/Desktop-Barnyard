#ifndef DESKTOPBARNYARDWINDOW_H
#define DESKTOPBARNYARDWINDOW_H

#include "BaseWindow.h"

class DesktopBarnyardWindow : public BaseWindow<DesktopBarnyardWindow> {

    void showButtons();
    HWND spawnCreatureButton();

public:
    DesktopBarnyardWindow();

    PCWSTR ClassName() const override { return L"Barnyard"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};



#endif