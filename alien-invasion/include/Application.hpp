#pragma once

#include <SDL3/SDL.h>


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
		SDL_RenderRect(mRenderer, &mRect); // Rendering rect
		SDL_RenderPresent(mRenderer);
	}

	void Update(){
	
	}


	// Main Game Loop 
	void Loop(){
		// Infinite loop
		while(mRun){
			Input();
			Render();
			Update();
		}
	}


	// Class members
	private:
		bool mRun{true};
		SDL_Window *mWindow;
		SDL_Renderer *mRenderer;
		SDL_FRect mRect{10.0f, 20.0f, 100.0f, 200.0f};
};
