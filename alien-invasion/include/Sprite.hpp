
#pragma once

#include <SDL3/SDL.h>


struct Sprite{

	Sprite();
	
	void CreateSprite(SDL_Renderer *renderer, const char *filePath);

	~Sprite();

	void Update(float deltaTime);
	void Render(SDL_Renderer *renderer);

	
	
	void SetW(float w);

	void SetH(float h);

	void SetX(float x);

	void SetY(float y);
	
	float GetX() const;

	float GetY() const;

	float GetW() const;

	float GetH() const;

	void Move(float x, float y);
	void Input(float deltaTime);

	
	SDL_FRect GetRectangle();

	private:
		
		// Rect x, y, w, h
		SDL_FRect mRect{20.0f, 20.0f, 10.0f, 10.0f};
		
	
		SDL_Texture *mTexture;
};

