#include "Main.h"


HINSTANCE hInstance = NULL;
HWND hWnd = NULL;
HDC hDC = NULL;
LPCWSTR windowClassName;

bool runWnd;
bool isFullScreen;

wchar_t* utf8_to_utf16(const char* str);
void showMessageBox(const char* title, const char* msg);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool createWindow(int width, int height, int bits, bool fullscreen);
void resizeWindow(int width, int height);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdList, int nCmd)
{
	isFullScreen = false;

	monitorSize.width = GetSystemMetrics(SM_CXSCREEN);
	monitorSize.height = GetSystemMetrics(SM_CYSCREEN);
	devSize.width = DEV_WIDTH;
	devSize.height = DEV_HEIGHT;

#if 1
	wndSize.width = monitorSize.width * 2 / 3;
	wndSize.height = wndSize.width * devSize.height / devSize.width;
#endif
	resizeWindow(wndSize.width, wndSize.height);

	if(!createWindow(wndSize.width, wndSize.height, 32, isFullScreen))
	{
		return 0;
	}

	RECT rt;
	GetWindowRect(hWnd, &rt);
	int wndX = monitorSize.width/2 - wndSize.width/2;
	int wndY = monitorSize.height/2 - wndSize.height/2;
	MoveWindow(hWnd, wndX, wndY, wndSize.width, wndSize.height, TRUE);

	runWnd = true;
	MSG msg;
	while( runWnd )
	{
		if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
#if 0		// GDI or OpenGL(ES)
			drawLib(hDC, drawGame);
			SwapBuffers(hDC);
#else		// GDI+
			//InvalidateRect(hWnd, NULL, TRUE);
#endif
		}
	}
	return 0;
}

wchar_t* utf8_to_utf16(const char* str)
{
	int length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wchar_t* s = (wchar_t*)malloc(sizeof(wchar_t)*length);
	MultiByteToWideChar(CP_UTF8, 0, str, strlen(str)+1, s, length);
	return s;
}

void showMessageBox(const char* title, const char* msg)
{
	wchar_t* wTitle = utf8_to_utf16(title);
	wchar_t* wMsg = utf8_to_utf16(msg);
	MessageBox(NULL, wMsg, wTitle, MB_OK);
	free( wTitle );
	free( wMsg );
}

bool createWindow(int width, int height, int bits, bool fullscreen)
{

	hInstance = GetModuleHandle(NULL);
		windowClassName = TEXT("ShootingGame");

		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = (WNDPROC)WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = windowClassName;
		if( !RegisterClass(&wc) )
		{
//			showMessageBox("Error", "wc");
			return false;
		}

		DWORD dwExStyle;
		DWORD dwStyle;
		if( fullscreen )
		{
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;
		}
		else// if( fullscreen==false )
		{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW;
		}
		RECT rect;
		rect.left = 0;
		rect.right = width;
		rect.top = 0;
		rect.bottom = height;
		AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);

		hWnd=CreateWindowEx(dwExStyle,
							windowClassName,
							windowClassName,
							dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
							0, 0,
							rect.right-rect.left,
							rect.bottom-rect.top,
							NULL,
							NULL,
							hInstance,
							NULL);
		if( !hWnd )
		{
//			showMessageBox("Error", "CreateWindowEx");
			return false;
		}
		hDC = GetDC(hWnd);

		ShowWindow(hWnd, SW_SHOW);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);

		return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		break;
	case WM_CLOSE:
		break;
	case WM_SIZING:
		resizeWindow(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_SIZE:
		resizeWindow(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_SETCURSOR:
		break;
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void resizeWindow(int width, int height)
{
	wndSize.width = width;
	wndSize.height = height;

	if(devSize.width/devSize.height < wndSize.width/wndSize.height)
	{
		viewport.pos.y = 0;
		viewport.size.height = wndSize.height;
		viewport.size.width = viewport.size.height * devSize.width / devSize.height;
		viewport.pos.x = (wndSize.width - viewport.size.width)/2;
	}
	if(devSize.width/devSize.height > wndSize.width/wndSize.height)
	{
		viewport.pos.x = 0; viewport.size.width = wndSize.width;
		viewport.size.height = viewport.size.width * devSize.height / devSize.width;
		viewport.pos.y = (wndSize.height-viewport.size.height)/2;
	}
	else
	{
		viewport.pos.x = viewport.pos.y = 0;
		viewport.size.width = wndSize.width;
		viewport.size.height = wndSize.height;
	}
}


















