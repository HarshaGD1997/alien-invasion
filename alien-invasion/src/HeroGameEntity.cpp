#include "HeroGameEntity.hpp"

HeroGameEntity::HeroGameEntity(SDL_Renderer *renderer, Sprite sprite, int mScreenWidth, int mScreenHeight) : GameEntity(sprite){ //delegating constructor

	mScreenW = mScreenWidth;
	mScreenH = mScreenHeight;
	Sprite sp;
	sp.CreateSprite(renderer,"./images/bulletNew.bmp");
	mProjectile = std::make_shared<Projectile>(sp);

}

HeroGameEntity::~HeroGameEntity(){

}

void HeroGameEntity::Input(float deltaTime){
	const Uint8 *state = SDL_GetKeyboardState(nullptr);
	if(state[SDL_SCANCODE_A]){
		//SDL_Log("Left key pressed");
		if( mSprite.GetX() <= 0){
			//mSprite.SetX(mSprite.GetX());
			//SDL_Log("%f",mSprite.GetX());
			mSprite.SetX(mScreenW-mSprite.GetW());
		} 
		mSprite.SetX(mSprite.GetX() - mSpeed * deltaTime);
	}
	else if(state[SDL_SCANCODE_D]){
		//SDL_Log("right key pressed");
		if( mSprite.GetX() >= (mScreenW)){
			//SDL_Log("%f",mSprite.GetX());
			mSprite.SetX(0);
		}
		mSprite.SetX(mSprite.GetX() + mSpeed * deltaTime);
	}

	if(state[SDL_SCANCODE_RETURN]){
		//SDL_Log("key");
		mProjectile -> Launch(mSprite.GetX(), mSprite.GetY(), true);	

	}

}

void HeroGameEntity::Update(float deltaTime){
	mProjectile -> Update(deltaTime);	



}

void HeroGameEntity::Render(SDL_Renderer *renderer){
	mProjectile->Render(renderer);
	mSprite.Render(renderer);
}

std::shared_ptr<Projectile>HeroGameEntity::GetProjectile() const{
	return mProjectile;
}

