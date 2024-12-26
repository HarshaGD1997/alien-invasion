#pragma once

#include <SDL3/SDL.h>
#include <cstdlib>

#include "GameEntity.hpp"
#include "Projectile.hpp"

struct EnemyGameEntity : public GameEntity{

	EnemyGameEntity(SDL_Renderer *renderer, Sprite sprite) : GameEntity(sprite){ //delegating constructor
		Sprite sp;
		sp.CreateSprite(renderer, "./images/bulletNew.bmp");
		mProjectile = std::make_shared<Projectile>(sp);
			
		
		// Random Launch time

		mMinLaunchTime += std::rand() % 10000;
	}

	virtual ~EnemyGameEntity(){
	
	}

	virtual void Input(float deltaTime) override{
	
	}

	virtual void Update(float deltaTime) override{
		mProjectile->Update(deltaTime);
		if(offset > 80){
			xPosDir = false;	
		}
		if(offset < -80){
			xPosDir = true;
		}


		if(xPosDir){
			mSprite.SetX(mSprite.GetX() + mSpeed * deltaTime);

			offset += mSpeed * deltaTime;

		}
		else{
			mSprite.SetX(mSprite.GetX() - mSpeed * deltaTime);
			offset -= mSpeed * deltaTime;
		
		
		}

		if(mRenderable){

			mProjectile->Launch(mSprite.GetX(), mSprite.GetY(), false, mMinLaunchTime);

		}
	
	}

	virtual void Render(SDL_Renderer *renderer){
		if(mRenderable){
			mProjectile->Render(renderer);
			mSprite.Render(renderer);
		}
		else{
		
		}

	}
	
	virtual std::shared_ptr<Projectile> GetProjectile() const {
		return mProjectile;
	}

	private:
		std::shared_ptr<Projectile> mProjectile;	
		bool xPosDir{true};
		float offset{0};
		float mSpeed{100};
		float mMinLaunchTime{5000.0f};

};


