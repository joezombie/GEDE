//	Lab_02 - T-637-GEDE - 22.Feb.2015
//	Johannes Gunnar Heidarsson (JohannesH10@ru.is)

#include "MyApplication.h"

int main() {
	MyApplication app;
	app.startup();

	while (app.keepRunning()){
		app.renderOneFrame();
	}

	return 0;
}