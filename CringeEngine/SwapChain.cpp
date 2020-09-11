#include "SwapChain.h"

SwapChain::SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device; //Gets the directx device

	DXGI_SWAP_CHAIN_DESC desc; //swap chain description object
	ZeroMemory(&desc, sizeof(desc)); //Makes sure memory is used effectively
	desc.BufferCount = 1; //The buffers used by windows for rendering
	desc.BufferDesc.Width = width; //Unga bunga gotta set width and height for buffer
	desc.BufferDesc.Height = height; //lmao same
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Sets the buffer format 
	desc.BufferDesc.RefreshRate.Numerator = 60; //Sets the refresh rate to 60 (in hz)
	desc.BufferDesc.RefreshRate.Denominator = 1; //Denomator for above
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //How buffers are used
	desc.OutputWindow = hwnd; //pass in handle to output window
	desc.SampleDesc.Count = 1; //virtual Pixels per pixel
	desc.SampleDesc.Quality = 0; //0 is base line 
	desc.Windowed = TRUE; //set windowed mode to true

	HRESULT hr = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain); //Creates the actual swap chain for window specified by HWND (window handle) parameter

	if (FAILED(hr)) 
	{
		return false;
	}

	//---Get the back buffer color and set it to render target view---
	ID3D11Texture2D* buffer = NULL; //Pointer to Texture2D buffer for swap chain 
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer); //Gets back buffer for DeviceContext class from swap chain

	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv); //Actually creates the render view
	buffer->Release(); //Releases the render target view buffer

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL); //Presents the render target through the swap chain

	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release(); //Releases swap chain 
	delete this; //Deletes the abstraction required when creating swapchain
	return true;
}

SwapChain::~SwapChain()
{
}
