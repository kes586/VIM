#include "TUIAdapter.h"
#include "Controller.h"

int main(int argc, char* argv[])
{
	TUIAdapter::init();

	Controller controller;
	controller.Menu();

	return 0;
}