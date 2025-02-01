#include "DesktopBarnyardWindow.h"

#define SPAWN_HANDLE 100
#define DESPAWN_HANDLE 101

DesktopBarnyardWindow::DesktopBarnyardWindow() { 
    HRESULT hr = S_OK;
    
    hr = CoCreateInstance(
    CLSID_WICImagingFactory,
    NULL,
    CLSCTX_INPROC_SERVER,
    IID_PPV_ARGS(&pWICFactory)
    );

    // Create D2D factory
    if (SUCCEEDED(hr)) {
        // Create D2D factory
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2D1Factory);
    }
}

LRESULT DesktopBarnyardWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
            case WM_QUIT:
                return 0;
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
                            spawnCreature();
                            return 0;
                        case DESPAWN_HANDLE:
                            despawnCreature();
                            return 0;
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

    despawnCreatureButton = CreateWindow(
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


void DesktopBarnyardWindow::despawnCreature(){
    if (!SpriteList.empty()) {
       Sprites* temp = SpriteList.back();
       SpriteList.pop_back();
       delete temp;
    }
}

void DesktopBarnyardWindow::spawnCreature(){
    Sprites* temp = new Sprites();
    temp->initialize(pD2D1Factory, pWICFactory);
    SpriteList.push_back(temp);
}