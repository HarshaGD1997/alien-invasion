#pragma once

#include <SDL3/SDL.h>


struct Application{
	Application(int argc, char **argv){
		
	}

	
	~Application(){

		ShutDown();
	}
	
	void ShutDown(){
		SDL_Quit();
	}

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("SDL Video failed");
	}

			
};
