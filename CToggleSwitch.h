#pragma once

#include <Windows.h>
#include <tchar.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

#define TOGGLESWITCH_CLASS_NAME         _T("ToggleSwitch")

namespace CToggleSwitch
{
    bool RegisterWndClass(HINSTANCE hInstance);

    HWND Create(HWND hParent,
        int id,
        int x,
        int y,
        int width,
        int height);

    bool IsChecked(HWND hSwitch);

    void Checked(HWND hSwitch);
    void UnChecked(HWND hSwitch);

    void Toggle(HWND hSwitch);

    void SetBgColor(HWND hSwitch, COLORREF colBg);
    void SetKnobColor(HWND hSwitch, COLORREF colKnob);
    void SetPlateColor(HWND hSwitch, COLORREF colPlate);
}
