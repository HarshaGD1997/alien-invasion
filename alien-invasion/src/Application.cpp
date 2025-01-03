#include "Application.hpp"

Application::Application(int argc, char **argv){

	// init SDL3 video

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("SDL Video failed");
	}
	else{
		SDL_Log("SDL_Video working");
	}

	StartUp();	
}

// Destructor 
Application::~Application(){

	ShutDown();
}

void Application::ShutDown(){
	// Destroying Renderer
	SDL_DestroyRenderer(mRenderer);

	// Destroying SDL_Window
	SDL_DestroyWindow(mWindow);


	// Quit function
	SDL_Quit();
}

void Application::StartUp(){
	// creating an SDL Window
	mWindow = SDL_CreateWindow("Alien Invasion", mScreenWidth, mScreenHeight, SDL_EVENT_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);

	if(nullptr == mWindow){
		SDL_Log("Error in creating SDL_Window");
	}



	SDL_GetWindowSize(mWindow, &mScreenWidth, &mScreenHeight);
	SDL_Log("%d %d", mScreenWidth, mScreenHeight);

	// Creating a SDL Renderer 
	// Making use of Hardware acceleration

	mRenderer = SDL_CreateRenderer(mWindow, NULL);	

	if(nullptr == mRenderer){
		SDL_Log("Failed to create renderer %s", SDL_GetError());
	}

	// Init for enemies 
	int row = 2;
	int col = 2;
	for(int i=0; i<80; i++){
		Sprite sp;

		sp.CreateSprite(mRenderer, "./images/enemy2.bmp");
		sp.SetW(sp.GetW() + 15);	
		sp.SetH(sp.GetH() + 15);

		if(i % 16  == 0){
			++row;
			col = 0;
		}
		sp.Move(col*100+160, row*50);
		col++;

		std::unique_ptr<EnemyGameEntity> ge = std::make_unique<EnemyGameEntity>(mRenderer, sp);
		enemies.push_back(std::move(ge));	
	}
		

	// Init for hero

	Sprite heroSprite;
	heroSprite.CreateSprite(mRenderer, "./images/heroImg.bmp");
	heroSprite.SetW(heroSprite.GetW()+20);
	heroSprite.SetH(heroSprite.GetH()+20);

	heroSprite.Move(mScreenWidth/2 , mScreenHeight - 100);

	hero = std::make_unique <HeroGameEntity>(mRenderer, heroSprite, mScreenWidth, mScreenHeight);

}

// Input method
void Application::Input(float deltaTime){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_EVENT_QUIT){
			mRun = false;
		}
	}
	// Handling SDL_GetKeyboardState after SDL_Poll

	hero -> Input(deltaTime);

}

// Rendering section
void Application::Render(){

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // setting background color to black
	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE); // setting the object color to white

	// render for enemies 	

	for(int i=0; i < enemies.size(); i++){
		enemies[i] -> Render(mRenderer);
	}

	hero -> Render(mRenderer);
	SDL_RenderPresent(mRenderer);

	

}

void Application::Update(float deltaTime){

	// Updating enemies
	for(int i=0; i < enemies.size(); i++){
		enemies[i] -> Update(deltaTime);
		bool enemyResult = enemies[i] -> Intersects(hero->GetProjectile());
		bool GameOver = hero -> Intersects(enemies[i]->GetProjectile()) && enemies[i]->IsRenderable() == true;
		if(true==enemyResult && true==enemies[i]->IsRenderable()){
			enemies[i] -> SetRenderable(false);
			mPoints += 1;
		}

		if(GameOver){
			SDL_Log("You died");
			SDL_Log("Score : %f",mPoints);
			mRun = false;
		}
	}

	//update hero

	hero -> Update(deltaTime);
}


// Main Game Loop 
void Application::Loop(float targetFPS){
	// Infinite loop
	Uint64 lastTime, currentTime, frameRateCount=0;
	lastTime = SDL_GetTicks();

	float deltaTime = 1.0f/targetFPS;

	while(mRun){
		Uint64 startOfFrame = SDL_GetTicks();
		Input(deltaTime);
		Update(deltaTime);
		Render();

		Uint64 elapsedTime = SDL_GetTicks()-startOfFrame;

		frameRateCount++;

		Uint64 delay = (1000/targetFPS)-elapsedTime;
		currentTime = SDL_GetTicks();
		//frame capping

		if(elapsedTime < (1000/targetFPS)){
			SDL_Delay(delay);
		}

		if(currentTime > lastTime + 1000){

			SDL_Log("%li : ",frameRateCount);
			deltaTime = 1.0f/frameRateCount;
			frameRateCount = 0;
			lastTime = SDL_GetTicks();
		}
	}
}



