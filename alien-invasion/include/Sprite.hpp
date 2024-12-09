
#include<cstdlib>
#include <vector>
#include <memory>


struct Sprite{

	Sprite(){
	
	}
	
	void CreateSprite(SDL_Renderer *renderer, const char *filePath){
		
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
	//
	
	void SetW(float w){
		mRect.w = w;
	}

	void SetH(float h){
		mRect.h = h;
	}

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

	float GetW() const {
		return mRect.x;
	}

	float GetH() const{
		return mRect.h;
	}

	void Move(float x, float y){
		mRect.x = x;
		mRect.y = y;
	}	
	
	void Input(float deltaTime){
	
	}

	
	SDL_FRect GetRectangle(){
		return mRect;
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

struct Projectile : public GameEntity{

	Projectile(Sprite sprite) : GameEntity(sprite){
		timeSinceLastLaunch = SDL_GetTicks();
		mRenderable = false;
	}



	void Launch(float x, float y, bool yDirIsUp, float minLaunchTime=3000){
		// Get current time and compute the delay for the projectile
		if(SDL_GetTicks() - timeSinceLastLaunch > minLaunchTime){
			timeSinceLastLaunch = SDL_GetTicks();
			mIsFiring=true;
			mYDirUp = yDirIsUp;
			mSprite.Move(x,y);	
		}
		
	}

	void Update(float deltaTime) override{
		if(mIsFiring){
			mRenderable = true;
			if(true == mYDirUp){
				mSprite.SetY(mSprite.GetY() - mSpeed * deltaTime);
			}
			else{
				mSprite.SetY(mSprite.GetY() + mSpeed * deltaTime);
			}
		}
		else{
			mRenderable = false;
		}

		if(mSprite.GetY() < 0.0f || mSpeed > 480.0f){
			mIsFiring = false;
		}
	
	}

	
	void Render(SDL_Renderer *renderer) override{
		if(mRenderable){
		
			mSprite.Render(renderer);
		}
		else{
		
		}
	}



	private:
		//Sprite mSprite;
		float mSpeed{200.0f};
		bool mYDirUp{true};
		bool mIsFiring{false};
		Uint64 timeSinceLastLaunch;
};

struct EnemyGameEntity : public GameEntity{

	EnemyGameEntity(SDL_Renderer *renderer, Sprite sprite) : GameEntity(sprite){ //delegating constructor
		Sprite sp;
		sp.CreateSprite(renderer, "./images/bulletNew.bmp");
		mProjectile = std::make_shared<Projectile>(sp);
			

		// Random Launch time

		mMinLaunchTime += std::rand() % 10000;
	}

	virtual ~EnemyGameEntity(){
	
	}

	virtual void Input(float deltaTime) override{
	
	}

	virtual void Update(float deltaTime) override{
		mProjectile->Update(deltaTime);
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

		if(mRenderable){

			mProjectile->Launch(mSprite.GetX(), mSprite.GetY(), false, mMinLaunchTime);

		}
	
	}

	virtual void Render(SDL_Renderer *renderer){
		if(mRenderable){
			mProjectile->Render(renderer);
			mSprite.Render(renderer);
		}
		else{
		
		}

	}
	
	virtual std::shared_ptr<Projectile> GetProjectile() const {
		return mProjectile;
	}

	private:
		std::shared_ptr<Projectile> mProjectile;	
		bool xPosDir{true};
		float offset{0};
		float mSpeed{100};
		float mMinLaunchTime{5000.0f};

};

struct HeroGameEntity : public GameEntity{

	HeroGameEntity(SDL_Renderer *renderer, Sprite sprite) : GameEntity(sprite){ //delegating constructor

		Sprite sp;
		sp.CreateSprite(renderer,"./images/bulletNew.bmp");
		mProjectile = std::make_shared<Projectile>(sp);
		sp.SetW(1000);
	}

	virtual ~HeroGameEntity(){
	
	}

	virtual void Input(float deltaTime) override{
		const Uint8 *state = SDL_GetKeyboardState(nullptr);
		if(state[SDL_SCANCODE_A]){
			//SDL_Log("Left key pressed");
			if( mSprite.GetX() <= 0){
				//mSprite.SetX(mSprite.GetX());
				//SDL_Log("%f",mSprite.GetX());
				mSprite.SetX(640);
			} 
			mSprite.SetX(mSprite.GetX() - mSpeed * deltaTime);
		}
		else if(state[SDL_SCANCODE_D]){
			//SDL_Log("right key pressed");
			if( mSprite.GetX() >= (640)){
				//SDL_Log("%f",mSprite.GetX());
				mSprite.SetX(0);
			}
			mSprite.SetX(mSprite.GetX() + mSpeed * deltaTime);
		}

		if(state[SDL_SCANCODE_RETURN]){
			//SDL_Log("key");
			mProjectile -> Launch(mSprite.GetX(), mSprite.GetY(), true);	
		
		}
			
	}

	virtual void Update(float deltaTime) override{
		mProjectile -> Update(deltaTime);	

		
	
	}

	virtual void Render(SDL_Renderer *renderer){
		mProjectile->Render(renderer);
		mSprite.Render(renderer);
	}
	
	std::shared_ptr<Projectile>GetProjectile() const{
		return mProjectile;
	}

	private:
		
		
		float mSpeed{100};
		std::shared_ptr<Projectile> mProjectile;
};
