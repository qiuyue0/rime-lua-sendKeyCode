#include "keycodes.h"

#if defined(_WIN32)
SHORT getKeyCode(const char* keyName) {
    if (keyName == NULL) {
        return -1; // Invalid key name
    }
    // Windows 版本
    if (strcmp(keyName, "SHIFT") == 0) return VK_SHIFT;
    if (strcmp(keyName, "CONTROL") == 0) return VK_CONTROL;
    if (strcmp(keyName, "CTRL") == 0) return VK_CONTROL;
    if (strcmp(keyName, "ALT") == 0) return VK_MENU;
    if (strcmp(keyName, "HOME") == 0) return VK_HOME;
    if (strcmp(keyName, "END") == 0) return VK_END;
    if (strcmp(keyName, "TAB") == 0) return VK_TAB;
    if (strcmp(keyName, "RETURN") == 0) return VK_RETURN;
    if (strcmp(keyName, "CAPSLOCK") == 0) return VK_CAPITAL;
    SHORT vkCode = VkKeyScanA(keyName[0]); // 处理单字符键
    if (vkCode == -1) return -1;
    return vkCode & 0xFF; // 只返回虚拟键码部分
}
#elif defined(__APPLE__)
CGKeyCode getKeyCode(const char* keyName) {
    if (keyName == NULL) {
        return -1; // Invalid key name
    }
    // 字母键
    if (strcmp(keyName, "a") == 0) return kVK_ANSI_A;
    if (strcmp(keyName, "b") == 0) return kVK_ANSI_B;
    if (strcmp(keyName, "c") == 0) return kVK_ANSI_C;
    if (strcmp(keyName, "d") == 0) return kVK_ANSI_D;
    if (strcmp(keyName, "e") == 0) return kVK_ANSI_E;
    if (strcmp(keyName, "f") == 0) return kVK_ANSI_F;
    if (strcmp(keyName, "g") == 0) return kVK_ANSI_G;
    if (strcmp(keyName, "h") == 0) return kVK_ANSI_H;
    if (strcmp(keyName, "i") == 0) return kVK_ANSI_I;
    if (strcmp(keyName, "j") == 0) return kVK_ANSI_J;
    if (strcmp(keyName, "k") == 0) return kVK_ANSI_K;
    if (strcmp(keyName, "l") == 0) return kVK_ANSI_L;
    if (strcmp(keyName, "m") == 0) return kVK_ANSI_M;
    if (strcmp(keyName, "n") == 0) return kVK_ANSI_N;
    if (strcmp(keyName, "o") == 0) return kVK_ANSI_O;
    if (strcmp(keyName, "p") == 0) return kVK_ANSI_P;
    if (strcmp(keyName, "q") == 0) return kVK_ANSI_Q;
    if (strcmp(keyName, "r") == 0) return kVK_ANSI_R;
    if (strcmp(keyName, "s") == 0) return kVK_ANSI_S;
    if (strcmp(keyName, "t") == 0) return kVK_ANSI_T;
    if (strcmp(keyName, "u") == 0) return kVK_ANSI_U;
    if (strcmp(keyName, "v") == 0) return kVK_ANSI_V;
    if (strcmp(keyName, "w") == 0) return kVK_ANSI_W;
    if (strcmp(keyName, "x") == 0) return kVK_ANSI_X;
    if (strcmp(keyName, "y") == 0) return kVK_ANSI_Y;
    if (strcmp(keyName, "z") == 0) return kVK_ANSI_Z;

    // 功能键
    if (strcmp(keyName, "F1") == 0) return kVK_F1;
    if (strcmp(keyName, "F2") == 0) return kVK_F2;
    if (strcmp(keyName, "F3") == 0) return kVK_F3;
    if (strcmp(keyName, "F4") == 0) return kVK_F4;
    if (strcmp(keyName, "F5") == 0) return kVK_F5;
    if (strcmp(keyName, "F6") == 0) return kVK_F6;
    if (strcmp(keyName, "F7") == 0) return kVK_F7;
    if (strcmp(keyName, "F8") == 0) return kVK_F8;
    if (strcmp(keyName, "F9") == 0) return kVK_F9;
    if (strcmp(keyName, "F10") == 0) return kVK_F10;
    if (strcmp(keyName, "F11") == 0) return kVK_F11;
    if (strcmp(keyName, "F12") == 0) return kVK_F12;

    // 特殊字符
    if (strcmp(keyName, " ") == 0) return kVK_Space;        // 空格
    if (strcmp(keyName, "\b") == 0) return kVK_Delete;       // Backspace
    if (strcmp(keyName, "\n") == 0) return kVK_Return;       // Enter
    if (strcmp(keyName, "\t") == 0) return kVK_Tab;          // Tab
    if (strcmp(keyName, "ESC") == 0) return kVK_Escape;      // Escape

    // 修改键
    if (strcmp(keyName, "SHIFT") == 0) return kVK_Shift;     // Shift
    if (strcmp(keyName, "CONTROL") == 0) return kVK_Control; // Control
    if (strcmp(keyName, "OPTION") == 0) return kVK_Option;   // Option
    if (strcmp(keyName, "COMMAND") == 0) return kVK_Command; // Command

    // 其他常用键
    if (strcmp(keyName, "HOME") == 0) return kVK_Home;       // Home
    if (strcmp(keyName, "END") == 0) return kVK_End;         // End
    if (strcmp(keyName, "PAGEUP") == 0) return kVK_PageUp;   // Page Up
    if (strcmp(keyName, "PAGEDOWN") == 0) return kVK_PageDown; // Page Down

    return -1;
}
#else
unsigned short getKeyCode(const char* keyName) {
    if (keyName == NULL) {
        return -1; // Invalid key name
    }
    // Linux 占位
    Display *display = XOpenDisplay(NULL);
    if (!display) return -1; // 无法打开显示
    KeyCode kc = 0;
    if (strcmp(keyName, "Shift") == 0) kc = XKeysymToKeycode(display, XK_Shift_L);
    else if (strcmp(keyName, "Control") == 0) kc = XKeysymToKeycode(display, XK_Control_L);
    else if (strcmp(keyName, "Alt") == 0) kc = XKeysymToKeycode(display, XK_Alt_L);
    else kc = XKeysymToKeycode(display, XStringToKeysym(keyName)); // 处理其他键
    XCloseDisplay(display);
    return (int)kc;
}
#endif
