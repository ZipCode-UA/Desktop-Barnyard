#include "DesktopBarnyardWindow.h"

#define SPAWN_HANDLE 100
#define DESPAWN_HANDLE 101

DesktopBarnyardWindow::DesktopBarnyardWindow() { }

LRESULT DesktopBarnyardWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        	case WM_CLOSE:
                PostQuitMessage(0);
                return 0;
            case WM_DESTROY: 
                return 0;
            case WM_CREATE:
                createButtons();
                return 0;
            // this is the message thats added to the mesage queue when a button is pushed
            case WM_COMMAND:
                {
                    switch (LOWORD(wParam)){
                        case SPAWN_HANDLE:
                            testSprite.initialize();
                            break;
                        case DESPAWN_HANDLE:
                            MessageBox(NULL, L"Despawn Creature Pushed", L"Temp MSG Box", 0);
                            break;
                    }   
                }
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

    spawnCreatureButton = CreateWindow(
        L"BUTTON", // predefined button class
        L"Remove Creature",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        220, 10, // (x, y) of top left corner
        200, 200, // width and height
        m_hwnd,
        (HMENU) DESPAWN_HANDLE,
        (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
        NULL);
}

