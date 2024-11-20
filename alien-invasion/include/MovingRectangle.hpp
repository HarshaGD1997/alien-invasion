
#include<cstdlib>


struct MovingRectangle{
	
	MovingRectangle(){
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

	void Update(){
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
			mRect.x += mSpeed;

		}
		else{
			mRect.x -= mSpeed;
		}
	
	}

	void Render(SDL_Renderer *renderer){
		SDL_RenderRect(renderer, &mRect);
	}


	
	

	private:
		// Rect x, y, w, h
		SDL_FRect mRect{20.0f, 20.0f, 50.0f, 100.0f};
		bool xPosDir;
		bool yPosDir;
		float mSpeed{1.0f};
		
};
