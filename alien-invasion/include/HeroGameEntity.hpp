#pragma once

#include <SDL3/SDL.h>
#include <memory>

#include "GameEntity.hpp"
#include "Projectile.hpp"

struct HeroGameEntity : public GameEntity{

	HeroGameEntity(SDL_Renderer *renderer, Sprite sprite, int mScreenWidth, int mScreenHeight);
	virtual ~HeroGameEntity();

	virtual void Input(float deltaTime) override;
	virtual void Update(float deltaTime) override;

	virtual void Render(SDL_Renderer *renderer);
	
	std::shared_ptr<Projectile>GetProjectile() const;

	private:
		
		int mScreenW;
		int mScreenH;
			
		float mSpeed{100};
		std::shared_ptr<Projectile> mProjectile;
};
