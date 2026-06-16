#include "AppW.h"
#include "Controls.h"

int main() {

	try {
		GraphicsEn::create();
		Controls::create();
	}
	catch (...) { return -1; }
	

	try{
		AppW app;
		while (app.isRun());
	}
	catch (...) { 
		Controls::release();
		GraphicsEn::release();
		return -1;
	}
	

	Controls::release();
	GraphicsEn::release();

	return 0;
}