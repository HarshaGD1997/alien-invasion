#pragma once

#include <SDL3/SDL.h>
#include "Sprite.hpp"


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

		// Init for enemies 

		for(int i=0; i<20; i++){
			Sprite sp;
			sp.CreateSprite(mRenderer, "./images/enemy2.bmp");
			enemies.emplace_back(sp); 
		}

		// Init for hero
		
		hero.CreateSprite(mRenderer, "./images/hero1.bmp");

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
		
	// render for enemies 	

		for(int i=0; i < enemies.size(); i++){
			enemies[i].Render(mRenderer);
		}

		hero.Render(mRenderer);
		SDL_RenderPresent(mRenderer);

	// render for hero
		//hero.Render(mRenderer);
		
	}

	void Update(float deltaTime){

		// updating enemies
		for(int i=0; i < enemies.size(); i++){
			enemies[i].Update(deltaTime);
		}

		//update hero

		hero.Update(deltaTime);
	}


	// Main Game Loop 
	void Loop(float targetFPS){
		// Infinite loop
		Uint64 lastTime, currentTime, frameRateCount=0;
		lastTime = SDL_GetTicks();
		
		float deltaTime = 1.0f/targetFPS;

		while(mRun){
			Uint64 startOfFrame = SDL_GetTicks();
			Input();
			Update(deltaTime);
			Render();
			
			Uint64 elapsedTime = SDL_GetTicks()-startOfFrame;
			
			frameRateCount++;
			
			Uint64 delay = (1000/targetFPS)-elapsedTime;
			currentTime = SDL_GetTicks();
			//frame capping

			if(elapsedTime < (1000/targetFPS)){
				SDL_Delay(delay);
			}

			if(currentTime > lastTime + 1000){
			
				SDL_Log("%li : ",frameRateCount);
				deltaTime = 1.0f/frameRateCount;
				frameRateCount = 0;
				lastTime = SDL_GetTicks();
			}
		}
	}


	// Class members
	private:
		// enimies 
		std::vector<Sprite> enemies;
		// hero

		Sprite hero;
		bool mRun{true};
		SDL_Window *mWindow;
		SDL_Renderer *mRenderer;
		
		
};
