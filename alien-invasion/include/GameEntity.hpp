#pragma once

#include <SDL3/SDL.h>
#include <memory>

#include "Sprite.hpp"

struct GameEntity{
	GameEntity(Sprite sprite);

	virtual ~GameEntity();

	virtual void Input(float deltaTime);

	
	virtual void Update(float deltaTime);

	virtual void Render(SDL_Renderer *renderer);

	void SetRenderable(bool collVal);

	

	bool Intersects(std::shared_ptr<GameEntity> e);

	bool IsRenderable() const;

	protected:
		Sprite mSprite;
		bool mRenderable{true};	
		
	
};


