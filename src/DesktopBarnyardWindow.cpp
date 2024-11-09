#include "DesktopBarnyardWindow.h"

DesktopBarnyardWindow::DesktopBarnyardWindow() { }

LRESULT DesktopBarnyardWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        	case WM_CLOSE:
                DestroyWindow(m_hwnd);
                return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            case WM_CREATE:
                return 0;
            case WM_PAINT:

            default:
                return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        }
        return 0;
}

void DesktopBarnyardWindow::createButtons(){
    spawnCreatureButton = CreateWindow(
        L"BUTTON", // predefined button class
        L"Spawn Creature",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, // (x, y) of top left corner
        200, 200, // width and height
        m_hwnd,
        (HMENU) SPAWN_HANDLE,
        (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
        NULL);
}

void DesktopBarnyardWindow::start(){
    createButtons();
}

