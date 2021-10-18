#include <iostream>
#include "./Window.h"

int main() {
    std::cout << "Creating Window" << std::endl;

    Window * window = new Window();

    bool run = true;   
    while(run) {
        if (!window->processMessages()) {
            std::cout << "Exiting Program" << std::endl;
            run = false;
        }

        Sleep(10);
    }

    delete window;

    return 0;
}