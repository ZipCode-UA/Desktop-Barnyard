#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <Windows.h>

namespace WindowTemplate{

    template <class T> void SafeRelease(T** ppT);

    template <class T>
    class BaseWindow
    {
    public:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        BaseWindow() : m_hwnd(NULL) { }

        BOOL Create(
            PCWSTR lpWindowName,
            DWORD dwStyle,
            DWORD dwExStyle = 0,
            int x = CW_USEDEFAULT,
            int y = CW_USEDEFAULT,
            int nWidth = CW_USEDEFAULT,
            int nHeight = CW_USEDEFAULT,
            HWND hWndParent = 0,
            HMENU hMenu = 0
        );

        HWND Window() const { return m_hwnd; }

    protected:

        virtual PCWSTR  ClassName() const = 0;
        virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

        HWND m_hwnd;
    };

}

#endif