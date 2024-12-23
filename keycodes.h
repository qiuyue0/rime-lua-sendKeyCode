#ifndef KEYCODES_H
#define KEYCODES_H

#if defined(_WIN32)
#include <windows.h>
SHORT getKeyCode(const char* keyName);
#elif defined(__APPLE__)
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
CGKeyCode getKeyCode(const char* keyName);
#else
#include <X11/keysym.h>
#include <X11/Xlib.h>
unsigned short getKeyCode(const char* keyName);
#endif

#endif // KEYCODES_H
