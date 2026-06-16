#pragma once
#include "InputReciver.h"
#include<map>
#include "Point.h"

class Controls
{
private:
	Controls();
	~Controls();
public :
	void update();
	void addReciver(InputReciver* Reciver);
	void removeReciver(InputReciver* Reciver);

	static Controls* get();
	static void create();
	static void release();
private:
	std::map< InputReciver*, InputReciver*> m_map_recivers;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point m_last_mouse_pos;
	bool m_first_time = true;
	static Controls* m_controls;
};

