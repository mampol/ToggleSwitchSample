#include <windows.h>
#include "CToggleSwitch.h"
#include "resource.h"

#define APP_CLASS			L"ToggleSwitchSmaple"
#define ID_BIG              1001
#define ID_NORMAL           1002
#define ID_SMALL            1003

LRESULT CALLBACK SampleDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
LRESULT OnInitDlg(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
LRESULT OnCommand(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
LRESULT OnDpiChanged(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

static int DpiScale(HWND hWnd, int value);
void LayoutControls(HWND hDlg);

int APIENTRY _tWinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPTSTR lpsCmdLine, int nCmdShow)
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	HANDLE hMutex = CreateMutex(NULL, TRUE, APP_CLASS);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		SetForegroundWindow(FindWindow(APP_CLASS, NULL));
		if (hMutex) CloseHandle(hMutex);
		return 0;
	}

	Gdiplus::GdiplusStartupInput gdiplusStartupInput = nullptr;
	ULONG_PTR gdiplusToken = 0;
	// GDI+初期化
	if (Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr) == Gdiplus::Ok) {

		// ダイアログ作成
		DialogBox(hCurInst, MAKEINTRESOURCE(IDD_SAMPLEBOX), nullptr, (DLGPROC)SampleDlgProc);

		Gdiplus::GdiplusShutdown(gdiplusToken);

	}

	if (hMutex) CloseHandle(hMutex);

	return 0;
}

LRESULT CALLBACK SampleDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return (OnInitDlg(hDlg, msg, wp, lp));
	case WM_COMMAND:
		return (OnCommand(hDlg, msg, wp, lp));
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_DPICHANGED:
		return (OnDpiChanged(hDlg, msg, wp, lp));
	default:
		return FALSE;
	}
	return TRUE;
}

LRESULT OnInitDlg(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	HINSTANCE hInst = reinterpret_cast<HINSTANCE>(GetWindowLongPtr(hDlg, GWLP_HINSTANCE));
	// ウィンドウクラス登録
	if (CToggleSwitch::RegisterWndClass(hInst)) {

		// スイッチ作成（大）
		HWND hSwitchBig = CToggleSwitch::Create(hDlg,
			ID_BIG,
			DpiScale(hDlg, 100),
			DpiScale(hDlg, 10),
			DpiScale(hDlg, 400),
			DpiScale(hDlg, 220));

		// スイッチ作成（中）
		HWND hSwitchNormal = CToggleSwitch::Create(hDlg,
			ID_NORMAL,
			DpiScale(hDlg, 100),
			DpiScale(hDlg, 250),
			DpiScale(hDlg, 100),
			DpiScale(hDlg, 60));
		// スイッチの色を設定
		CToggleSwitch::SetBgColor(hSwitchNormal, RGB(96, 96, 96));
		CToggleSwitch::SetKnobColor(hSwitchNormal, RGB(220, 20, 20));
		CToggleSwitch::SetPlateColor(hSwitchNormal, RGB(20, 220, 20));

		// スイッチ作成（小）
		HWND hSwitchSmall = CToggleSwitch::Create(hDlg,
			ID_SMALL,
			DpiScale(hDlg, 100),
			DpiScale(hDlg, 330),
			DpiScale(hDlg, 50),
			DpiScale(hDlg, 30),
			RGB(20, 220, 20),
			true);
	}
	return TRUE;
}

LRESULT OnCommand(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (LOWORD(wp))
	{
	case ID_BIG:
		if (CToggleSwitch::IsChecked(GetDlgItem(hDlg, ID_BIG))) {
			MessageBox(hDlg, L"BIG ON", APP_CLASS, MB_ICONINFORMATION);
		}
		break;
	case ID_NORMAL:
		if (CToggleSwitch::IsChecked(GetDlgItem(hDlg, ID_NORMAL))) {
			MessageBox(hDlg, L"NORMAL ON", APP_CLASS, MB_ICONINFORMATION);
		}
		break;
	case ID_SMALL:
		if (CToggleSwitch::IsChecked(GetDlgItem(hDlg, ID_SMALL))) {
			MessageBox(hDlg, L"SMALL ON", APP_CLASS, MB_ICONINFORMATION);
		}
		break;
	}
	return TRUE;
}

LRESULT OnDpiChanged(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	RECT* prcNewWindow = reinterpret_cast<RECT*>(lp);

	SetWindowPos(hDlg,
		nullptr,
		prcNewWindow->left,
		prcNewWindow->top,
		prcNewWindow->right - prcNewWindow->left,
		prcNewWindow->bottom - prcNewWindow->top,
		SWP_NOZORDER | SWP_NOACTIVATE);

		return 0;
}

int DpiScale(HWND hWnd, int value)
{
	UINT dpi = GetDpiForWindow(hWnd);
	return MulDiv(value, dpi, 96);
}

void LayoutControls(HWND hDlg)
{
	MoveWindow(GetDlgItem(hDlg, ID_BIG),
		DpiScale(hDlg, 100),
		DpiScale(hDlg, 10),
		DpiScale(hDlg, 400),
		DpiScale(hDlg, 220),
		TRUE);

	MoveWindow(GetDlgItem(hDlg, ID_NORMAL),
		DpiScale(hDlg, 100),
		DpiScale(hDlg, 250),
		DpiScale(hDlg, 100),
		DpiScale(hDlg, 60),
		TRUE);

	MoveWindow(GetDlgItem(hDlg, ID_SMALL),
		DpiScale(hDlg, 100),
		DpiScale(hDlg, 330),
		DpiScale(hDlg, 50),
		DpiScale(hDlg, 30),
		TRUE);
}
