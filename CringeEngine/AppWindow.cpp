#include "AppWindow.h"

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate(); //Uses callback from "Window" class
	GraphicsEngine::get()->init(); //Initializes graphics engine
	m_swap_chain = GraphicsEngine::get()->createSwapChain(); //Creates swap chain for directX

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top); //Initializes swap chain with all of the data
}

void AppWindow::onDestroy()
{
	Window::onDestroy(); //uses callback from "Window" class
	m_swap_chain->release(); //Releases swap chain
	GraphicsEngine::get()->release(); //Releases graphics engine
}

void AppWindow::onUpdate()
{
	Window::onUpdate(); //Uses callback from "Window" class
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 1, 0, 1); //Sets the render target color to green
	m_swap_chain->present(false); //Presents the render target
}
