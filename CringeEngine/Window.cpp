#include "Window.h"

Window* window = nullptr; //Pointer to the window

Window::Window() 
{
	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) //Window event callback method
{
	switch (msg) 
	{
	case WM_CREATE:
		window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams; //Sets callback info
		SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)window); //Stores window info for later lookup
		window->setHWND(hwnd); //Sets window handle
		window->onCreate();
		break;
	case WM_DESTROY:
		window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0); //Quits the window with code 0 (successful)
		break;
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;     
}

bool Window::init()
{
	WNDCLASSEX wc; //Defines properties for window

	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Loads the icon, come back here later when want to change icon 
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //Funny icon loading
	wc.hInstance = NULL; //Have no current instance
	wc.lpszClassName = L"CringeEngineWindowClass"; //Class that contains all the properties of the window 
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc; //How we handle window events like calling the window and other things like that

	/// <summary>
	/// NOTE L = Pre-Append LPCSTR from string
	/// </summary>
	/// <returns> String->LPCSTR </returns>

	if (!::RegisterClassEx(&wc)) //Registers wc memory location and if failed will return false
	{
		return false;
	}

	/*
	if (!window)
	{
		window = this; //Sets the pointer to the window before creating window so we don't get null pointer exception
	}
	*/

	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"CringeEngineWindowClass", L"CringeEngine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, 
		NULL, NULL, NULL, this); //Creates the window and initializes the instance

	if (!m_hwnd) //If the creation of window instance fails, it will return false
	{
		return false;
	}

	::ShowWindow(m_hwnd, SW_SHOW); //Shows window to user
	::UpdateWindow(m_hwnd); //Updates window

	m_is_running = true; //Sets flag (to true) to initialize window if its up and running properly

	return true;
}

bool Window::broadcast()
{
	MSG msg; //window message

	this->onUpdate(); //Update callback to be used when we want to do stuff like render frames
	//Moved it up to prevent nullptr 

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) //Peeks at messages until queue is empty
	{
		TranslateMessage(&msg); //Translates message
		DispatchMessage(&msg); //Dispatches message to window procedure
	}
	     

	Sleep(1); //While this may seem like we are doing nothing but what we are actually doing is preventing the cpu from throttling by pausing ever so slightly

	return true;
}

bool Window::detatch()
{
	//Destroy Window
	if (!::DestroyWindow(m_hwnd))
	{
		return false;
	}

	return true;
}

bool Window::isRunning()
{
	return m_is_running;
}

void Window::onCreate()
{
}

void Window::onDestroy()
{
	m_is_running = false; //Window is not running anymore
}

void Window::onUpdate()
{
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc); //Gets client window width and height from window handle
	return rc; //returns client rect
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd; //Sets window handle to appropriate hwnd value
}

Window::~Window()
{

}