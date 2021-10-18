#include <windows.h>
#include <shellapi.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window {
    public:
        // disabling copy constuctor
        Window();
        Window(const Window&) = delete;
        Window& operator = (Window&) = delete;
        ~Window();

        bool processMessages();
    private:
        HINSTANCE m_hInstance;
        HWND m_hWnd;
};