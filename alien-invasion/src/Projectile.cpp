#include "Projectile.hpp"

Projectile::Projectile(Sprite sprite) : GameEntity(sprite){
		timeSinceLastLaunch = SDL_GetTicks();
		mRenderable = false;
	}



	void Projectile::Launch(float x, float y, bool yDirIsUp, float minLaunchTime){
		// Get current time and compute the delay for the projectile
		if(SDL_GetTicks() - timeSinceLastLaunch > minLaunchTime){
			timeSinceLastLaunch = SDL_GetTicks();
			mIsFiring=true;
			mYDirUp = yDirIsUp;
			mSprite.Move(x,y);	
		}
		
	}

	void Projectile::Update(float deltaTime){
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

	
	void Projectile::Render(SDL_Renderer *renderer){
		if(mRenderable){
		
			mSprite.Render(renderer);
		}
		else{
		
		}
	}


