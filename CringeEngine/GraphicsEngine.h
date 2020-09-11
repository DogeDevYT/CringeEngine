#pragma once

#include <d3d11.h> //DirectX 11 already comes installed with windows in Windows 8 onwards

class SwapChain;
class DeviceContext;

class GraphicsEngine
{
public:
	GraphicsEngine();
	//Initialize Graphic Engine and DirectX 11 Framework
	bool init();
	//Releases DirectX 11 and the (graphics) engine
	bool release();
	~GraphicsEngine();

public:
	SwapChain* createSwapChain(); //Creates a swap chain
	DeviceContext* getImmediateDeviceContext(); //Gets the immediate device context from the device context class
public:
	static GraphicsEngine* get(); //GraphicsEngine Singleton
private:
	DeviceContext* m_imm_device_context; //Pointer to the immediate device context from custom context class
private:
	ID3D11Device* m_d3d_device; //Pointer to DirectX device
	D3D_FEATURE_LEVEL* m_feature_level; //Pointer to the feature level
	ID3D11DeviceContext* m_imm_context; //Pointer to immeadiate device context in DirectX

	IDXGIDevice* m_dxgi_device; //Pointer to XGI device   
	IDXGIAdapter* m_dxgi_adapter; //Pointer to XGI device's adapter
	IDXGIFactory* m_dxgi_factory; //Pointer to the XGI Factory class
private:
	friend class SwapChain; //Makes swapchain a friend class of GraphicsEngine so private members of graphicsengine can be accessed by swapchain
};

