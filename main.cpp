#define WIN32_LEAN_AND_MEAN
#include <sdkddkver.h>
#include <Windows.h>
#include <iostream>
#include <d2d1_3.h>
#include "Graphics.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        graphics->beginDraw();
        graphics->cleanScreen(0.222f, 0.180f, 0.203f);
        graphics->drawCircle(350, 300, 50, 0.0f, 0.0f, 0.5f, 1.0f);
        graphics->endDraw();
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOW;
    const wchar_t className[] = L"Snake";
    WNDCLASSEX windowClass;
    ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = className;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClassEx(&windowClass);

    RECT rect = { 280, 84, 1080, 684 }; //left, top, right, bottom
    uint32_t rectWidth = rect.right - rect.left;
    uint32_t rectHeight = rect.bottom - rect.top;

    HWND hwnd = CreateWindowExW(0, className, L"Snake", WS_POPUP | WS_CLIPCHILDREN, rect.left, rect.top, rectWidth, rectHeight, NULL, NULL, hInstance, NULL);

    try 
    {
        graphics = new Graphics(hwnd);
    }
    catch (...) 
    { 
        std::cout << "graphics was not created";
        throw 1; 
    }

    if (hwnd == 0)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    delete graphics;
    return 0;
}
