#pragma once

#include <Windows.h>

class Window
{
public:
	Window(); //Constructor
	bool init(); //Initializes window
	bool broadcast(); //Picks window messages from OS
	bool detatch(); //Releases the window
	bool isRunning(); //Is the window currently running?

	//Events
	virtual void onCreate();
	virtual void onDestroy();
	virtual void onUpdate();

	//Gets window dimensions
	RECT getClientWindowRect(); //Gets size and dimensions of window

	//Sets window handle
	void setHWND(HWND hwnd);

	~Window(); //Destructor
protected:
	HWND m_hwnd; //The window instance
	bool m_is_running; //member is running boolean
};

