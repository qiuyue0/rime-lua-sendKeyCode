#ifndef KEYCODES_H
#define KEYCODES_H

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <Carbon/Carbon.h>  // 需要使用 Carbon 框架进行键码的查找
#else
#include <X11/keysym.h>
#include <X11/Xlib.h>
#endif

// 通用函数声明
SHORT getKeyCode(const char* keyName);

#endif // KEYCODES_H
