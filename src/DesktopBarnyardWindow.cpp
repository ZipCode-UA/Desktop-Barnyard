#include "DesktopBarnyardWindow.h"

DesktopBarnyardWindow::DesktopBarnyardWindow() {
    showButtons();
}

LRESULT DesktopBarnyardWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        }
        return 0;
}

void DesktopBarnyardWindow::showButtons(){

}

