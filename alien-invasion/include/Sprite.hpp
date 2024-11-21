
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
		
	
		
	}

	~Sprite(){
	
		// TODO: Resource management
		//SDL_DestroyTexture(mTexture);
	}

	void Update(float deltaTime){
		
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

	//void Update(float deltaTime){}

	void SetX(float x){
		mRect.x = x;
	
	}

	void SetY(float y){
		mRect.y = y;
	}
	
	float GetX() const {
	
		return mRect.x;
	}

	float GetY() const {
	
		return mRect.y;
	}

	void Move(float x, float y){
		mRect.x = x;
		mRect.y = y;
	}	
	
	void Input(float deltaTime){
	
	}

	private:
		// Rect x, y, w, h
		SDL_FRect mRect{20.0f, 20.0f, 32.0f, 32.0f};
		
	
		SDL_Texture *mTexture;
};

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
		mSprite.Render(renderer);
	}

	protected:
		Sprite mSprite;
		
		
	
};

struct EnemyGameEntity : public GameEntity{

	EnemyGameEntity(Sprite sprite) : GameEntity(sprite){ //delegating constructor
	
	}

	virtual ~EnemyGameEntity(){
	
	}

	virtual void Input(float deltaTime) override{
	
	}

	void Update(float deltaTime) override{
		if(offset > 80){
			xPosDir = false;	
		}
		if(offset < -80){
			xPosDir = true;
		}


		if(xPosDir){
			mSprite.SetX(mSprite.GetX() + mSpeed * deltaTime);

			offset += mSpeed * deltaTime;

		}
		else{
			mSprite.SetX(mSprite.GetX() - mSpeed * deltaTime);
			offset -= mSpeed * deltaTime;
		}

		
	
	}

	//virtual void Render(SDL_Renderer *renderer){
	//	mSprite.Render(renderer);
	//}
	private:
		
		bool xPosDir{true};
		float offset{0};
		float mSpeed{100};

};

struct HeroGameEntity : public GameEntity{

	HeroGameEntity(Sprite sprite) : GameEntity(sprite){ //delegating constructor
	
	}

	virtual ~HeroGameEntity(){
	
	}

	virtual void Input(float deltaTime) override{
		const Uint8 *state = SDL_GetKeyboardState(nullptr);
		if(state[SDL_SCANCODE_A]){
			//SDL_Log("Left key pressed");
			mSprite.SetX(mSprite.GetX() - mSpeed * deltaTime);
		}
		else if(state[SDL_SCANCODE_D]){
			//SDL_Log("right key pressed");
			mSprite.SetX(mSprite.GetX() + mSpeed * deltaTime);
			}
			
	}

	void Update(float deltaTime) override{
	

		
	
	}

	//virtual void Render(SDL_Renderer *renderer){
	//	mSprite.Render(renderer);
	//}
	private:
		

		float mSpeed{150};

};
