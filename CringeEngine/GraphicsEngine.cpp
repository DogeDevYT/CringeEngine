#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] = //Sort through drivers best to worst
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] = 
	{
		D3D_FEATURE_LEVEL_11_0	
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);  

	HRESULT res = 0;
	ID3D11DeviceContext* m_imm__context;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, m_feature_level, &m_imm_context); //Creates device
		if (SUCCEEDED(res))
		{
			break;
		}
	}

	if (FAILED(res))
	{
		return false; //Device creation failed
	}

	m_imm_device_context = new DeviceContext(m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice),(void**) &m_dxgi_device); //Gets XGI device (required for swap chain)
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**) &m_dxgi_adapter); //Gets XGI device adapter
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**) &m_dxgi_factory); //Gets XGI Factory class for swapchain class to create swapchain
    
	return true;
}

bool GraphicsEngine::release()
{
	m_dxgi_device->Release(); //Releases all DXGI resources
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release(); //Release all DirectX resources through the device context manager class

	m_d3d_device->Release();
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain(); //Creates a whole new swapchain
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context; //Returns the immediate device context from the device context class
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine; //Creates only one instace of graphicsengine in memory when run then stores its location as to create effective singleton instead of creating more and wasting memory
}
