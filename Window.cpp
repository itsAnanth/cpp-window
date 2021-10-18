#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include "./Window.h"


// handles all events happening in a window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
Window::Window() : m_hInstance(GetModuleHandle(nullptr)) {
    
    // setting up a new window
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    const wchar_t WINDOW_TITLE[] = L"Sample Window";
    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    // registering a new window using a pointer to wndClass
    WNDCLASS * winPtr = &wndClass;
    RegisterClass(winPtr);

    // caption makes a title bar and use bitwise or to combine minimize, close btn etc
    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;


    // window dimensions
    int width = 600;
    int height = 400;
    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    // setting outer border dimensions for window
    AdjustWindowRect(&rect, style, false);

    // creating a new window
    m_hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        WINDOW_TITLE,
        style,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        m_hInstance,
        NULL
    );

    // show the window
    ShowWindow(m_hWnd, SW_SHOW);

}


Window::~Window() {

    // unregister window after use
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    UnregisterClass(CLASS_NAME, m_hInstance);
    std::cout << "Successfully unregistered window class" << std::endl;
}

bool Window::processMessages() {
    MSG msg = {};

    while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

        if (msg.message == WM_QUIT) 
            return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}