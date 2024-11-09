#include "Sprites.h"

    Sprites::Sprites(){
        if (!Create(L"TestSprite", WS_POPUP, WS_EX_LAYERED | WS_EX_TRANSPARENT)){
            throw "Failed to create sprite window";
        }
    }

    HRESULT Sprites::CreateGraphicsResources(){
        HRESULT hr;
        // Later when we have multiple sprites, we will need to make this a multithreaded factory (I think)
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
    }

    LRESULT Sprites::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

    }