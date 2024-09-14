/**
 * combile: g++ -o x11 x11.cpp -lX11
 */

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include <cstdlib>

void executeCommand(const char* command) {
    system(command);
}

int main() {
    // Open a connection to the X server
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Unable to open X display" << std::endl;
        return 1;
    }

    // Get the default screen
    int screen = DefaultScreen(display);

    // Define window properties
    int width = 800;
    int height = 600;
    int x = 100; // X position
    int y = 100; // Y position
    Window root = RootWindow(display, screen);

    // Create a simple window
    // Window window = XCreateWindow(
        // display,                     // Display
        // root,                       // Parent window
        // x, y,                       // Position
        // width, height,             // Size
        // 0,                          // Border width
        // CopyFromParent,            // Border depth
        // InputOutput,               // Window class
        // CopyFromParent,            // Visual
        // 0,                          // Value mask
        // nullptr                     // Additional attributes
    // );
// 
    // // Set the title of the window
    // XStoreName(display, window, "My X11 Window");

    // Map (show) the window
    // XMapWindow(display, window);

    // Define the key combination to listen for (Shift + Alt + R)
    KeyCode shiftKey = XKeysymToKeycode(display, XK_Shift_L);
    KeyCode altKey = XKeysymToKeycode(display, XK_Alt_L);
    KeyCode rKey = XKeysymToKeycode(display, XK_r);

    // if(XUngrabKey(display, rKey, ShiftMask | Mod1Mask, root) != 0) {
      // std::cout << "fail to ungrab" << std::endl;
    // }
    // Grab the key combination globally
    XGrabKey(display, rKey, ShiftMask | Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);

    std::cout << "Listening for Shift + Alt + R globally..." << std::endl;

    // Main event loop
    XEvent event;
    while (true) {
        XNextEvent(display, &event);

        // Check if the event is a key press
        if (event.type == KeyPress) {
            if (event.xkey.keycode == rKey) {
                // Check if Control and Alt are pressed
                // if (event.xkey.state & ShiftMask && event.xkey.state & Mod1Mask) {
                    std::cout << "Shift + Alt + R pressed!" << std::endl;
                    executeCommand("notify-send key pressed");  // Replace with your command
                // }
            }
        }
    }

    // Cleanup (not reached in this example)
    XCloseDisplay(display);
    return 0;
}

