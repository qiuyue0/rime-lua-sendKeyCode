#include "keycodes.h"

SHORT getKeyCode(const char* keyName) {
    if (keyName == NULL) {
        return -1; // Invalid key name
    }

#if defined(_WIN32)
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

#elif defined(__APPLE__)
    // macOS 版本，占位
    if (strcmp(keyName, "SHIFT") == 0) return kVK_Shift;
    if (strcmp(keyName, "CONTROL") == 0) return kVK_Control;
    if (strcmp(keyName, "ALT") == 0) return kVK_Option;
    if (strcmp(keyName, "COMMAND") == 0) return kVK_Command;
    if (strcmp(keyName, "ENTER") == 0) return kVK_Return;
    if (strcmp(keyName, "SPACE") == 0) return kVK_Space;
    if (strcmp(keyName, "HOME") == 0) return kVK_Home;
    if (strcmp(keyName, "END") == 0) return kVK_End;
    if (strcmp(keyName, "TAB") == 0) return kVK_Tab;
    return -1;

#else
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
#endif
}
