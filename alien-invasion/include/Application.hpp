#pragma once

#include <vector>
#include <cstdlib>

#include <SDL3/SDL.h>
#include "EnemyGameEntity.hpp"
#include "HeroGameEntity.hpp"
#include "GameEntity.hpp"
#include "Projectile.hpp"

struct Application{
	
	
	Application(int argc, char **argv);

 
	~Application();
	
	void ShutDown();

	void StartUp();	
	
	void Input(float deltaTime);
	
	void Render();

	void Update(float deltaTime); 
	void Loop(float targetFPS);
	

	private:
		 
		std::vector<std::unique_ptr<EnemyGameEntity>> enemies;
		

		std::unique_ptr<HeroGameEntity> hero;
		bool mRun{true};
		float mPoints{0.0f};
		SDL_Window *mWindow;
		SDL_Renderer *mRenderer;
		int mScreenWidth = 0;
		int mScreenHeight = 0;	
		
};
