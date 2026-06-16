#pragma once
#include "Point.h"

class InputReciver {
public:
	InputReciver() {

	}
	~InputReciver() {

	}

	//Keyboard
	virtual void Keyon(int key) = 0;
	virtual void Keyoff(int key) = 0;
	//Mouse
	virtual void Mousedynamic(const Point& delta_mouse_pos) = 0;
	virtual void LeftMouseON(const Point& mouse_pos) = 0;
	virtual void LeftMouseOFF(const Point& mouse_pos) = 0;
	virtual void RightMouseON(const Point& mouse_pos) = 0;
	virtual void RightMouseOFF(const Point& mouse_pos) = 0;
};
