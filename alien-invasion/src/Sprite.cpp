
#include "Sprite.hpp"

Sprite::Sprite(){

}

void Sprite::CreateSprite(SDL_Renderer *renderer, const char *filePath){

	SDL_Surface *pixels = SDL_LoadBMP(filePath);
	const SDL_PixelFormatDetails *formatDetails = SDL_GetPixelFormatDetails(pixels->format);
	/*SDL_SetSurfaceColorKey(pixels, SDL_TRUE, SDL_MapRGB(formatDetails,NULL, 193, 11, 229));




	  mTexture = SDL_CreateTextureFromSurface(renderer, pixels);

	  if(nullptr == mTexture){
	  SDL_Log("Could not load image");
	  }

	  SDL_DestroySurface(pixels);

*/

	Uint32 colorKey1 = SDL_MapRGB(formatDetails, NULL, 193, 11, 229);



	if(SDL_MUSTLOCK(pixels)){
		SDL_LockSurface(pixels);
	}

	SDL_SetSurfaceColorKey(pixels, SDL_TRUE, colorKey1);
	//SDL_SetSurfaceColorKey(pixels, SDL_TRUE, colorKey2);

	if(SDL_MUSTLOCK(pixels)){
		SDL_UnlockSurface(pixels);
	}

	//SDL_SetSurfaceBlendMode(pixels, SDL_BLENDMODE_NONE);
	mTexture = SDL_CreateTextureFromSurface(renderer, pixels);

	if(nullptr == mTexture){
		SDL_Log("Could not create texture %s",SDL_GetError());
	}

	SDL_DestroySurface(pixels);

}

Sprite::~Sprite(){

	// TODO: Resource management
	//SDL_DestroyTexture(mTexture);
}

void Sprite::Update(float deltaTime){

}

void Sprite::Render(SDL_Renderer *renderer){
	if(nullptr == mTexture){
		SDL_RenderRect(renderer, &mRect);
	}
	else{
		SDL_RenderTexture(renderer, mTexture, nullptr, &mRect);
	}
	//SDL_RenderRect(renderer, &mRect);
}

//void Update(float deltaTime){}
//

void Sprite::SetW(float w){
	mRect.w = w;
}

void Sprite::SetH(float h){
	mRect.h = h;
}

void Sprite::SetX(float x){
	mRect.x = x;

}

void Sprite::SetY(float y){
	mRect.y = y;
}

float Sprite::GetX() const {

	return mRect.x;
}

float Sprite::GetY() const {

	return mRect.y;
}

float Sprite::GetW() const {
	return mRect.x;
}

float Sprite::GetH() const{
	return mRect.h;
}

void Sprite::Move(float x, float y){
	mRect.x = x;
	mRect.y = y;
}	

void Sprite::Input(float deltaTime){

}


SDL_FRect Sprite::GetRectangle(){
	return mRect;
}

