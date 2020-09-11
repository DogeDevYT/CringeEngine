#pragma once

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

class AppWindow : public Window //Inherit from Window class
{
public:
	AppWindow(); //Constructor 
	~AppWindow(); //Destructor

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void onUpdate() override;
private:
	SwapChain* m_swap_chain; //Pointer to the swap chain being created
};

