#pragma once

#include <SDL3/SDL.h>
#include <memory>

struct GameEntity{
	GameEntity(Sprite sprite){
		
		mSprite = sprite;
	}

	virtual ~GameEntity(){
	
	}

	virtual void Input(float deltaTime){
	
	}

	
	virtual void Update(float deltaTime){
		

		
	
	}
	virtual void Render(SDL_Renderer *renderer){

	}

	void SetRenderable(bool collVal){
		//mRenderable = !(collVal);
		mRenderable = collVal;
	}

	// Collision detection

	bool Intersects(std::shared_ptr<GameEntity> e){
		SDL_FRect source = e->mSprite.GetRectangle();
		SDL_FRect us = mSprite.GetRectangle();
		SDL_FRect result;
		return (SDL_GetRectIntersectionFloat(&source, &us, &result));
	}

	bool IsRenderable() const{
		return mRenderable;
	}	

	protected:
		Sprite mSprite;
		bool mRenderable{true};	
		
	
};


