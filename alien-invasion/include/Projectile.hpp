#pragma once

#include <SDL3/SDL.h>
#include "GameEntity.hpp"
#include "Projectile.hpp"

struct Projectile : public GameEntity{

	Projectile(Sprite sprite);


	void Launch(float x, float y, bool yDirIsUp, float minLaunchTime=3000);
		
	

	void Update(float deltaTime);
	
	void Render(SDL_Renderer *renderer);


	private:
		//Sprite mSprite;
		float mSpeed{200.0f};
		bool mYDirUp{true};
		bool mIsFiring{false};
		Uint64 timeSinceLastLaunch;
};


