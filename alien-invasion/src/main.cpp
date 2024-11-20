#include "Application.hpp"

int main(int argc, char **argv){

	float targetFPS = 60;
	Application app(argc, argv);
	app.Loop(targetFPS);

	return 0;
}
