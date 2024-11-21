
#include<cstdlib>
#include <vector>


struct Sprite{

	Sprite(){
	
	}
	
	void CreateSprite(SDL_Renderer *renderer, const char *filePath){
		
		SDL_Surface *pixels = SDL_LoadBMP(filePath);
		const SDL_PixelFormatDetails *formatDetails = SDL_GetPixelFormatDetails(pixels->format);
		SDL_SetSurfaceColorKey(pixels, SDL_TRUE, SDL_MapRGB(formatDetails,NULL, 193, 11, 229));

		

		mTexture = SDL_CreateTextureFromSurface(renderer, pixels);
		
		if(nullptr == mTexture){
			SDL_Log("Could not load image");
		}

		SDL_DestroySurface(pixels);
		
		xPosDir = true;
		
	}

	~Sprite(){
	
		// TODO: Resource management
		//SDL_DestroyTexture(mTexture);
	}

	void Update(float deltaTime){
		if(offset > 80){
			xPosDir = false;	
	}
		if(offset < -80){
			xPosDir = true;
		}


		if(xPosDir){
			mRect.x += mSpeed * deltaTime;
			offset += mSpeed * deltaTime;

		}
		else{
			mRect.x -= mSpeed * deltaTime;
			offset -= mSpeed * deltaTime;
		}

		
	
	}

	void Render(SDL_Renderer *renderer){
		if(nullptr == mTexture){
			SDL_RenderRect(renderer, &mRect);
		}
		else{
			SDL_RenderTexture(renderer, mTexture, nullptr, &mRect);
		}
		//SDL_RenderRect(renderer, &mRect);
	}


	
	void Move(float x, float y){
		mRect.x = x;
		mRect.y = y;
	}	

	private:
		// Rect x, y, w, h
		SDL_FRect mRect{20.0f, 20.0f, 32.0f, 32.0f};
		bool xPosDir{true};
		bool yPosDir;
		float offset{0};
		float mSpeed{100.0f};
		SDL_Texture *mTexture;
};
