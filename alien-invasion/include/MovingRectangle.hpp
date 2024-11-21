
#include<cstdlib>
#include <vector>


struct MovingRectangle{
	
	MovingRectangle(SDL_Renderer *renderer){
		
		SDL_Surface *pixels = SDL_LoadBMP("./images/enemy2.bmp");
		const SDL_PixelFormatDetails *formatDetails = SDL_GetPixelFormatDetails(pixels->format);
		SDL_SetSurfaceColorKey(pixels, SDL_TRUE, SDL_MapRGB(formatDetails,NULL, 193, 11, 229));

		

		mTexture = SDL_CreateTextureFromSurface(renderer, pixels);
		
		if(nullptr == mTexture){
			SDL_Log("Could not load image");
		}

		SDL_DestroySurface(pixels);

		mSpeed *= std::rand()%10 / 100.0f; // Randomize speed
		mRect.x = std::rand()% 640;
		mRect.y = std::rand() % 480;
		//SDL_Log("%f, %f", mRect.x, mRect.y);
		// making sure size is not 0

		mRect.w = std::rand() % 50 + 10;
		mRect.h = std::rand() % 50 + 10;

		// handling directions

		xPosDir = std::rand() % 1;
		yPosDir = std::rand() % 1;
	}

	~MovingRectangle(){
	
		// TODO: Resource management
		//SDL_DestroyTexture(mTexture);
	}

	void Update(float deltaTime){
		if(mRect.x > 640.0f - mRect.w){
			xPosDir = false;	
	}
		if(mRect.x < 0.0f){
			xPosDir = true;
		}

		if(mRect.y > 480.0f - mRect.h){
		
			yPosDir = false;
		}

		if(mRect.y < 0.0f){
			yPosDir = true;
		}

		if(xPosDir){
			mRect.x += mSpeed * deltaTime;

		}
		else{
			mRect.x -= mSpeed * deltaTime;
		}

		if(yPosDir){
			mRect.y += mSpeed * deltaTime;
		}
		else{
			mRect.y -= mSpeed * deltaTime;
		}
	
	}

	void Render(SDL_Renderer *renderer){
		if(nullptr == mTexture){
			SDL_RenderRect(renderer, &mRect);
		}
		else{
			SDL_RenderTexture(renderer, mTexture, nullptr, &mRect);
		}
		SDL_RenderRect(renderer, &mRect);
	}


	
	

	private:
		// Rect x, y, w, h
		SDL_FRect mRect{20.0f, 20.0f, 50.0f, 100.0f};
		bool xPosDir;
		bool yPosDir;
		float mSpeed{1000.0f};
		SDL_Texture *mTexture;
};
