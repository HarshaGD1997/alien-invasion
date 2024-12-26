#include "EnemyGameEntity.hpp"


EnemyGameEntity::EnemyGameEntity(SDL_Renderer *renderer, Sprite sprite) : GameEntity(sprite){ //delegating constructor
	Sprite sp;
	sp.CreateSprite(renderer, "./images/bulletNew.bmp");
	mProjectile = std::make_shared<Projectile>(sp);


	// Random Launch time

	mMinLaunchTime += std::rand() % 10000;
}

EnemyGameEntity::~EnemyGameEntity(){

}

void EnemyGameEntity::Input(float deltaTime){

}

void EnemyGameEntity::Update(float deltaTime){
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

void EnemyGameEntity::Render(SDL_Renderer *renderer){
	if(mRenderable){
		mProjectile->Render(renderer);
		mSprite.Render(renderer);
	}
	else{

	}

}

std::shared_ptr<Projectile> EnemyGameEntity::GetProjectile() const {
	return mProjectile;
}


