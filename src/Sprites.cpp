#include "Sprites.h"

    Sprites::Sprites(){
        if (!Create(L"TestSprite", WS_POPUP, WS_EX_LAYERED | WS_EX_TRANSPARENT)){
            throw "Failed to create sprite window";
        }
    }

    HRESULT Sprites::CreateGraphicsResources(){
        HRESULT hr;
    }

    LRESULT Sprites::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

    }