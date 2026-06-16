#include "Controls.h"
#include <Windows.h>
Controls* Controls::m_controls = nullptr;


Controls::Controls(){
}

Controls::~Controls(){
	Controls::m_controls = nullptr;
}

void Controls::update(){

	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);
	if (m_first_time) {
		m_last_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}
	if (current_mouse_pos.x != m_last_mouse_pos.m_x || current_mouse_pos.y != m_last_mouse_pos.m_y) {
		//mose is dynamic
		std::map< InputReciver*, InputReciver*>::iterator it = m_map_recivers.begin();
		while (it != m_map_recivers.end()) {
			it->second->Mousedynamic(Point(current_mouse_pos.x - m_last_mouse_pos.m_x, current_mouse_pos.y - m_last_mouse_pos.m_y));
			++it;
		}

	}
	m_last_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

	if (::GetKeyboardState(m_keys_state)) {
		for (unsigned int i = 0; i < 256; i++) {
			if (m_keys_state[i] & 0x80) {
				//key on
				std::map< InputReciver*, InputReciver*>::iterator it = m_map_recivers.begin();
				while (it != m_map_recivers.end()) {
					if (i == VK_LBUTTON) {
						if (m_keys_state[i] != m_old_keys_state[i])
							it->second->LeftMouseON(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else if (i == VK_RBUTTON) {
						if (m_keys_state[i] != m_old_keys_state[i])
							it->second->RightMouseON(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else {
						it->second->Keyon(i);
					}
					++it;
				}
			}
			else {
				//key off
				if (m_keys_state[i] != m_old_keys_state[i]) {
					std::map< InputReciver*, InputReciver*>::iterator it = m_map_recivers.begin();
					while (it != m_map_recivers.end()) {
						if (i == VK_LBUTTON) {
							it->second->LeftMouseOFF(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						else if (i == VK_RBUTTON) {
							it->second->RightMouseOFF(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						else {
							it->second->Keyoff(i);
						}
						++it;
					}

				}
			}
		}
		//storing the last key state
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void Controls::addReciver(InputReciver* Reciver){

	m_map_recivers.insert(std::make_pair<InputReciver*, InputReciver*>
		(std::forward<InputReciver*>(Reciver), std::forward<InputReciver*>(Reciver)));
}

void Controls::removeReciver(InputReciver* Reciver){
	std::map< InputReciver*, InputReciver*>::iterator it = m_map_recivers.find(Reciver);
	if (it != m_map_recivers.end()) {
		m_map_recivers.erase(it);
	}
}

Controls* Controls::get(){
	static Controls system;
	return &system;
}

void Controls::create() {
	if (Controls::m_controls) throw std::exception("Controls shat its pants twice");
	Controls::m_controls = new Controls();
}

void Controls::release() {
	if (Controls::m_controls) return;
	delete Controls::m_controls;
}
