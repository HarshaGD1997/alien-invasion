#pragma once

#include <SDL3/SDL.h>
#include "MovingRectangle.hpp"


struct Application{
	
	// Constructor 
	Application(int argc, char **argv){
		
		// init SDL3 video
		 
		if(SDL_Init(SDL_INIT_VIDEO) != 0){
			SDL_Log("SDL Video failed");
		}
		else{
			SDL_Log("SDL_Video working");
		}

		StartUp();	
	}

	// Destructor 
	~Application(){

		ShutDown();
	}
	
	void ShutDown(){
		// Destroying Renderer
		SDL_DestroyRenderer(mRenderer);

		// Destroying SDL_Window
		SDL_DestroyWindow(mWindow);

		
		// Quit function
		SDL_Quit();
	}

	void StartUp(){
		// creating an SDL Window
		mWindow = SDL_CreateWindow("Alien Invasion", 640, 480, SDL_EVENT_WINDOW_SHOWN);
		
		if(nullptr == mWindow){
			SDL_Log("Error in creating SDL_Window");
		}


		// Creating a SDL Renderer 
		// Making use of Hardware acceleration

		mRenderer = SDL_CreateRenderer(mWindow, NULL);	
	
		if(nullptr == mRenderer){
			SDL_Log("Failed to create renderer %s", SDL_GetError());
		}

	}
	
	// Input method
	void Input(){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_EVENT_QUIT){
				mRun = false;
			}
		}
	}

	// Rendering section
	void Render(){
		
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // setting background color to black
		SDL_RenderClear(mRenderer);
		SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE); // setting the object color to white
		
		

		for(int i=0; i<30; i++){
			mRect[i].Render(mRenderer);
		}

		SDL_RenderPresent(mRenderer);
		
	}

	void Update(){
		for(int i=0; i < 30; i++){
			mRect[i].Update();
		}
	}


	// Main Game Loop 
	void Loop(){
		// Infinite loop
		Uint64 lastTime, currentTime, frameRateCount=0;
		lastTime = SDL_GetTicks();
		
		while(mRun){
			Input();
			Update();
			Render();
			
			frameRateCount++;

			currentTime = SDL_GetTicks();
			if(currentTime > lastTime + 1000){
			
				SDL_Log("%li : ",frameRateCount);
				frameRateCount = 0;
				lastTime = SDL_GetTicks();
			}
		}
	}


	// Class members
	private:
		MovingRectangle mRect[30];
		bool mRun{true};
		SDL_Window *mWindow;
		SDL_Renderer *mRenderer;
		
		
};
