#pragma once

#include <d3d11.h>

class SwapChain;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context); //Singleton creation for devicecontext

	bool clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha); //Clears the rendertarget (basically rendering layer) with a color
	bool release(); //Releases device context from memory

	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context; //Pointer to device context
};

