#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <Windows.h>

class Window{
public:
	Window();
	bool isRun();

	RECT getClientWindowRect();
	virtual void onCreate() ;
	virtual void onUpdate() ;
	virtual void onDestroy() ;
	virtual void WinActive();
	virtual void WinInactive();
	~Window();
private:
	bool broadcast();
protected:
	HWND m_hwnd;
	bool m_is_run;
	bool m_is_init = false;
};

