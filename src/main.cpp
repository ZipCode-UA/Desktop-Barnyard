#ifndef UNICODE
#define UNICODE
#endif 

#include "DesktopBarnyardWindow.h"

#include <iostream>
#include <exception>

#include <Windows.h>

int main(){

    // Initialize COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        MessageBox(NULL, L"Failed to initialize COM", L"Error", MB_OK);
    }

    // Create main window    
    DesktopBarnyardWindow window;
    if (!window.Create(L"Barnyard", WS_OVERLAPPEDWINDOW)) {
        MessageBox(NULL, L"Failed to create window.", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }
    ShowWindow(window.Window(), 1);

    // Start message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Uninitialize COM
    CoUninitialize();
}