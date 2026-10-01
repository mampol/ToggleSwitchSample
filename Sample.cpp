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

int APIENTRY _tWinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPTSTR lpsCmdLine, int nCmdShow)
{
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
			100, 10,
			400, 220);

		// スイッチ作成（中）
		HWND hSwitchNormal = CToggleSwitch::Create(hDlg,
			ID_NORMAL,
			100, 250,
			100, 60);
		// スイッチの色を設定
		CToggleSwitch::SetBgColor(hSwitchNormal, RGB(96, 96, 96));
		CToggleSwitch::SetKnobColor(hSwitchNormal, RGB(220, 20, 20));
		CToggleSwitch::SetPlateColor(hSwitchNormal, RGB(20, 220, 20));

		// スイッチ作成（小）
		HWND hSwitchSmall = CToggleSwitch::Create(hDlg,
			ID_SMALL,
			100, 330,
			50, 30,
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
