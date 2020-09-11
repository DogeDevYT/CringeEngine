#pragma once

#include "GraphicsEngine.h"
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	bool init(HWND hwnd, UINT width, UINT height); //Inits swap chain for a window

	bool present(bool vsync); //Presents the render target

	bool release(); //Releases swap chain for a window
	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain; //Pointer to actual swap chain
	ID3D11RenderTargetView* m_rtv; //Pointer to render target view
private:
	friend class DeviceContext; //DeviceContext can access private members of SwapChain
};

