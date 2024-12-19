#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <ApplicationServices/ApplicationServices.h>
#else
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#endif

static void press_key(const char* keyName, int count) {
#if defined(_WIN32)
    // Windows implementation
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = VkKeyScan(*keyName);  // Assumes first character of keyName is the key to press
    ip.ki.dwFlags = 0;  // 0 for key press
    for (int i = 0; i < count; i++) {
        SendInput(1, &ip, sizeof(INPUT));
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
        ip.ki.dwFlags = 0;  // Reset to 0 for next key press
    }
#elif defined(__APPLE__)
    // macOS implementation
    CGEventRef eventDown, eventUp;
    eventDown = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)*keyName, true);
    eventUp = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)*keyName, false);
    for (int i = 0; i < count; i++) {
        CGEventPost(kCGHIDEventTap, eventDown);
        CGEventPost(kCGHIDEventTap, eventUp);
    }
    CFRelease(eventDown);
    CFRelease(eventUp);
#else
    // Linux implementation (requires X11)
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) return;  // Handle error appropriately
    KeyCode kc = XKeysymToKeycode(display, XStringToKeysym(keyName));
    for (int i = 0; i < count; i++) {
        XTestFakeKeyEvent(display, kc, True, 0);
        XTestFakeKeyEvent(display, kc, False, 0);
        XFlush(display);
    }
    XCloseDisplay(display);
#endif
}

static int l_press_key(lua_State *L) {
    const char *keyName = luaL_checkstring(L, 1);
    int count = luaL_checkinteger(L, 2);
    press_key(keyName, count);
    return 0;
}

static const struct luaL_Reg mylib [] = {
    {"press_key", l_press_key},
    {NULL, NULL}
};

__declspec(dllexport) int luaopen_sendKeyCode(lua_State *L) {
    luaL_newlib(L, mylib);
    return 1;
}
