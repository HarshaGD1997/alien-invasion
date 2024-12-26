#pragma once

#include <SDL3/SDL.h>


struct Projectile : public GameEntity{

	Projectile(Sprite sprite) : GameEntity(sprite){
		timeSinceLastLaunch = SDL_GetTicks();
		mRenderable = false;
	}



	void Launch(float x, float y, bool yDirIsUp, float minLaunchTime=3000){
		// Get current time and compute the delay for the projectile
		if(SDL_GetTicks() - timeSinceLastLaunch > minLaunchTime){
			timeSinceLastLaunch = SDL_GetTicks();
			mIsFiring=true;
			mYDirUp = yDirIsUp;
			mSprite.Move(x,y);	
		}
		
	}

	void Update(float deltaTime) override{
		if(mIsFiring){
			mRenderable = true;
			if(true == mYDirUp){
				mSprite.SetY(mSprite.GetY() - mSpeed * deltaTime);
			}
			else{
				mSprite.SetY(mSprite.GetY() + mSpeed * deltaTime);
			}
		}
		else{
			mRenderable = false;
		}

		if(mSprite.GetY() < 0.0f || mSpeed > 480.0f){
			mIsFiring = false;
		}
	
	}

	
	void Render(SDL_Renderer *renderer) override{
		if(mRenderable){
		
			mSprite.Render(renderer);
		}
		else{
		
		}
	}



	private:
		//Sprite mSprite;
		float mSpeed{200.0f};
		bool mYDirUp{true};
		bool mIsFiring{false};
		Uint64 timeSinceLastLaunch;
};


