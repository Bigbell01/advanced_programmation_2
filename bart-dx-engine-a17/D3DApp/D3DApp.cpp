#include "stdafx.h"

#include "D3DApp.h"

extern D3DApp* gD3DApp = 0;
extern IDirect3DDevice9* gD3DDevice = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	if (gD3DApp != 0)
	{
		return gD3DApp->MsgProc(msg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

D3DApp::D3DApp()
	: devType(D3DDEVTYPE_HAL)
	, requestedVP(D3DCREATE_HARDWARE_VERTEXPROCESSING)
	, appPaused(false)
{
	// Initialise captions
	// Initialise les chaînes globales
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_D3DAPP, szWindowClass, MAX_LOADSTRING);

	OpenConsole();
}

D3DApp::~D3DApp()
{
}

void D3DApp::Init(HINSTANCE hInstance, int cmdShow)
{
	Init(hInstance, cmdShow, 800, 600);
}

void D3DApp::Init(HINSTANCE hInstance, int cmdShow, int width, int height)
{
	this->hInstance = hInstance;

	if (!InitMainWindow(cmdShow, width, height))
	{
		MessageBox(0, L"InitMainWindow - Failed", 0, 0);
		PostQuitMessage(0);
	}

	if (!InitDirect3D())
	{
		MessageBox(0, L"InitDirect3D - Failed", 0, 0);
		PostQuitMessage(0);
	}

	// Make the app accessible to all
	gD3DApp = this;
}

LRESULT D3DApp::MsgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analyse les sélections de menu :
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hMainWindow, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hMainWindow);
			break;
		default:
			return DefWindowProc(hMainWindow, msg, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hMainWindow, &ps);
		// TODO: ajoutez le code de dessin qui utilise hdc ici...
		EndPaint(hMainWindow, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hMainWindow, msg, wParam, lParam);
	}
	return 0;
}

int D3DApp::InitMainWindow(int nCmdShow, int width, int height)
{
	// Register class
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D3DAPP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_D3DAPP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (!RegisterClassExW(&wcex))
	{
		return FALSE;
	}

	// Create the window
	hMainWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);

	if (!hMainWindow)
	{
		return FALSE;
	}

	ShowWindow(hMainWindow, nCmdShow);
	UpdateWindow(hMainWindow);

	return TRUE;
}

int D3DApp::InitDirect3D()
{
	// Step 1
	d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3dObject)
		return FALSE;

	// Step 2
	D3DDISPLAYMODE mode;
	HR(d3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode));
	HR(d3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, devType, mode.Format, mode.Format, true));
	HR(d3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, devType, mode.Format, mode.Format, false));

	// Step 3
	D3DCAPS9 caps;
	HR(d3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, devType, &caps));

	DWORD devBehaviourFlags = 0;
	devBehaviourFlags |= (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		? D3DCREATE_HARDWARE_VERTEXPROCESSING
		: D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	if ((caps.DevCaps & D3DDEVCAPS_PUREDEVICE) &&
		(devBehaviourFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING))
	{
		devBehaviourFlags |= D3DCREATE_PUREDEVICE;
	}

	// Step 4
	d3dpp.BackBufferWidth = 0;
	d3dpp.BackBufferHeight = 0;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hMainWindow;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 5
	HR(d3dObject->CreateDevice(D3DADAPTER_DEFAULT, devType, nullptr, devBehaviourFlags, &d3dpp, &gD3DDevice));

	return TRUE;
}

void D3DApp::OpenConsole()
{
	//standard input/ output/ error file pointers
	FILE *fpStdIn, *fpStdOut, *fpStdErr;

	// Enable run-time memory check for debug build
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (AllocConsole())
	{
		//Assign the stdin/ stdout/ stderr streams to the newly created console
		_tfreopen_s(&fpStdIn, _T("CONIN$"), _T("r"), stdin);
		_tfreopen_s(&fpStdOut, _T("CONOUT$"), _T("w"), stdout);
		_tfreopen_s(&fpStdErr, _T("CONOUT$"), _T("w"), stderr);
	}
#endif
}

int D3DApp::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//gDInput = new DirectInput(GetAppInstance(), GetMainWindow(),
	//	DISCL_NONEXCLUSIVE | DISCL_FOREGROUND,
	//	DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	//
	//gTimer = new GameTimer();
	//gTimer->Reset();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (appPaused)
			{
				Sleep(20);
				continue;
			}

			//if (!GetDeviceLost())
			{
				//gDInput->poll();
				//gTimer->Tick();
				Update();
				Draw();
			}
		}
	}
	return (int)msg.wParam;
}

void D3DApp::Update()
{

}

void D3DApp::Draw()
{

}




