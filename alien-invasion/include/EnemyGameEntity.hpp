#pragma once

#include <SDL3/SDL.h>


#include "GameEntity.hpp"
#include "Projectile.hpp"



struct EnemyGameEntity : public GameEntity{

	EnemyGameEntity(SDL_Renderer *renderer, Sprite sprite);

	virtual ~EnemyGameEntity();

	virtual void Input(float deltaTime) override;

	virtual void Update(float deltaTime) override;

	virtual void Render(SDL_Renderer *renderer);
	
	virtual std::shared_ptr<Projectile> GetProjectile() const;

	private:
		std::shared_ptr<Projectile> mProjectile;	
		bool xPosDir{true};
		float offset{0};
		float mSpeed{100};
		float mMinLaunchTime{5000.0f};

};


