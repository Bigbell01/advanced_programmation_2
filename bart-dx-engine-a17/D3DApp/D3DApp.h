#pragma once

#include "stdafx.h"
#include "resource.h"

#include "D3DUtils.h"

#define MAX_LOADSTRING 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

class D3DApp
{
public:
	D3DApp();
	virtual ~D3DApp();

	HWND GetMainWindow() { return hMainWindow; }
	HINSTANCE GetAppInstance() { return hInstance; }

	virtual LRESULT MsgProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void Init(HINSTANCE hInstance, int cmdShow);
	virtual void Init(HINSTANCE hInstance, int cmdShow, int width, int height);
	virtual int Run();

protected:
	D3DPRESENT_PARAMETERS d3dpp;

	virtual int InitMainWindow(int nCmdShow, int width, int height);
	virtual int InitDirect3D();
	virtual bool CheckDeviceCaps() { return true; }
	virtual void Update();
	virtual void Draw();

	//void ResetDevice();

private:
	void OpenConsole();

	IDirect3D9* d3dObject;
	bool appPaused;
	HWND hMainWindow;
	HINSTANCE hInstance;
	std::string mainWindowCaption;

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];

	D3DDEVTYPE devType;
	DWORD requestedVP;
};

extern D3DApp* gD3DApp;
extern IDirect3DDevice9* gD3DDevice;

