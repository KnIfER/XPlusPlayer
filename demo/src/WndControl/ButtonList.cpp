
#include "ButtonList.h"

#include "../resource.h"



ButtonList::ButtonList(HINSTANCE hInstance, HWND hParent)
{
	DWORD style = 
		WS_CHILD | WS_VISIBLE 
		| WS_CLIPCHILDREN | WS_CLIPSIBLINGS 
		| TBSTYLE_TOOLTIPS 
		| TBSTYLE_FLAT 
		//| CCS_NODIVIDER | CCS_NORESIZE | CCS_NOPARENTALIGN
		| CCS_BOTTOM
		| CCS_NODIVIDER
		;

	// WS_VISIBLE|WS_CHILD|TBSTYLE_FLAT|TBSTYLE_TOOLTIPS

	_hWnd = CreateWindowEx(0, TOOLBARCLASSNAME, TEXT("toolbar"),
		style ,
		0, 0, 0, 0,
		hParent,
		(HMENU)0,
		hInstance,
		NULL);


	HIMAGELIST images = ImageList_Create(38, 38
		, ILC_COLOR32 | ILC_MASK, 3, 1);

	//ImageList_SetIconSize


	ImageList_AddIcon(images
		, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAY)));
	ImageList_AddIcon(images
		, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STOP)));
	ImageList_AddIcon(images
		, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PREV)));
	ImageList_AddIcon(images
		, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NXT)));
	ImageList_AddIcon(images
		, LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FOLDER)));

	SendWndMessage(TB_SETIMAGELIST, 0, (LPARAM)images);


	TBBUTTON buttonInfo[] =
	{
		{ 0, IDM_START,       TBSTATE_ENABLED
		, TBSTYLE_BUTTON|TBSTYLE_GROUP, {0}, 0, 0 }
		,{ 1, IDM_STOP,      TBSTATE_ENABLED, TBSTYLE_BUTTON|TBSTYLE_GROUP, {0}, 0, 0 }
		,{ 2, IDM_PREV,     TBSTATE_ENABLED, TBSTYLE_BUTTON|TBSTYLE_GROUP, {0}, 0, 0 }
		,{ 3, IDM_NXT,    TBSTATE_ENABLED, TBSTYLE_BUTTON|TBSTYLE_GROUP, {0}, 0, 0 }
		,{ 4, IDM_OPEN,    TBSTATE_ENABLED, TBSTYLE_BUTTON|TBSTYLE_GROUP, {0}, 0, 0 }
	};
	SendWndMessage(TB_ADDBUTTONS, 5, (LPARAM)&buttonInfo);



	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);




}



// Adds one or more buttons to a ButtonList. pButtonInfoArray is a pointer to an array of TBBUTTON.
// Refer to TB_ADDBUTTONS in the Windows API documentation for more information.
BOOL ButtonList::AddButtons(UINT buttonCount, LPTBBUTTON pButtonInfoArray)
{
    return SendWndMessage(TB_ADDBUTTONS, (WPARAM)buttonCount, (LPARAM)pButtonInfoArray) != 0;
}


// Retrieves information about the specified button in a ButtonList.
// Refer to TB_GETBUTTON in the Windows API documentation for more information.
int ButtonList::GetCommandAt(int index)
{
	TBBUTTON tbb;
	ZeroMemory(&tbb, sizeof(tbb));
	SendWndMessage(TB_GETBUTTON, (WPARAM)index, (LPARAM)&tbb);

	// returns zero if failed
	return tbb.idCommand;
}



void ButtonList::showWindow()
{
	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);
}


LRESULT ButtonList::RunProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	if (_SysWndProc)
	{
		::CallWindowProc(_SysWndProc, hwnd, msg, w, l);
	}
	return ::DefWindowProc(hwnd, msg, w, l);
}

//static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
//{
//	GetWindowLongPtr(hwnd, GWLP_USERDATA);
//	static TCHAR s[] = TEXT("Hello, Windows.");
//	switch (msg)
//	{
//	case WM_DRAWITEM:
//	{
//		break;
//	}
//	case WM_CREATE:
//		return 0;
//	case WM_PAINT:
//		HDC hdc;
//		PAINTSTRUCT ps;
//		RECT rect;
//		GetClientRect(hwnd, &rect);
//		hdc = BeginPaint(hwnd, &ps);
//		DrawText (hdc, s, -1, &rect,DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
//		EndPaint(hwnd, &ps);
//		return 0;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//	case WM_SIZE:
//		if (_hWnd)
//		{
//			RECT rect;
//			GetClientRect(_hParent, &rect);
//			MoveWindow(_hWnd, rect.left, rect.top, rect.right, rect.bottom, true);
//		}
//		return 0;
//	case WM_QUIT:
//		return 0;
//	}
//}