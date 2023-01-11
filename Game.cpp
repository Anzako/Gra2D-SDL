#include "headers/Game.h"
#include "headers/GameObject.h"
#include "headers/TextureManager.h"
#include "headers/Map.h"
#include "headers/Player.h"
#include "headers/GameObject.h"

Map map;
Map* maps;
int mapNumber = 0;
Player* player1;
Player* player2;
int player1wins = 0;
int player2wins = 0;

GameObject* arrow;
SDL_RendererFlip flipType = SDL_FLIP_NONE;
int angle = 0;
myVector objectivePosition;

myVector player1beginPosition;
myVector player2beginPosition;
float scale = 1;
float frameTime;

SDL_Renderer* Game::gRenderer = nullptr;

const int JOYSTICK_DEAD_ZONE = 8000;
SDL_Joystick* gGameController = NULL;

float distanceToPeak = 30.0f;
float jumpHeight = 100.0f;
bool isOnGround = true;

myVector player2Velocity;
myVector player2Przemieszczenie;
float velY = 0;
//myVector player2Acc;

float jump_velocity = (2 * jumpHeight * 100) / distanceToPeak;
float gravity = (2 * jumpHeight * 100 * 100)
/ (distanceToPeak * distanceToPeak);
float jumpTime = 0;
float mapSpeed1 = 0.5f;
float mapSpeed2 = 0.6f;
float mapSpeed3 = 0.7f;


Game::Game(int width, int height) {
	// delta time
	NOW = SDL_GetPerformanceCounter();
	LAST = 0;
	deltaTime = 0;
	srand(time(NULL));

	ScreenWidth = width;
	ScreenHeight = height;
	TileSize = 40;
	//int mapWidth;		dodac
	//int maHeight;
	
	directionPlayer1 = { 0, 0 };
	directionPlayer2 = { 0, 0 };

	

	player2keyboardControl = false;
}

myVector drawPlayerPosition(Map mapa) {
	
	float playerX;
	float playerY;

	for (;;) {
		playerX = 1 + rand() % mapa.columns -2;
		playerY = 1 + rand() % mapa.rows -2;

		if (mapa.getTileNumber(playerX, playerY) != 3) {
			break;
		}
	}
	
	myVector wektor = { playerX * mapa.tSize, playerY * mapa.tSize };
	return wektor;
}

Game::~Game() {}

bool Game::init(const char* title, bool fullscreen) {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		//{
		//	printf("Warning: Linear texture filtering not enabled!");
		//}
		//if (SDL_NumJoysticks() < 1)
		//{
		//	player2keyboardControl = true;
		//	printf("Warning: No joysticks connected!\n");
		//}
		//else
		//{
		//	//Load joystick
		//	gGameController = SDL_JoystickOpen(0);
		//	if (gGameController == NULL)
		//	{
		//		player2keyboardControl = true;
		//		printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		//	}
		//}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
		maps = new Map[4];
		map = Map{ 16, 84, ScreenWidth, ScreenHeight, TileSize, "../assets/mapFile.txt" };
		maps[0] = map;
		map = Map{ 16, 84, ScreenWidth, ScreenHeight, TileSize, "../assets/mapFile2.txt" };
		maps[1] = map;
		map = Map{ 6, 28, ScreenWidth, ScreenHeight, 120, "../assets/mapFile3.txt" };
		maps[2] = map;
		map = Map{ 6, 28, ScreenWidth, ScreenHeight, 120, "../assets/mapFile4.txt" };
		maps[3] = map;
		//objectivePosition = map.getObjective();

		arrow = new GameObject("../assets/arrow.png", ScreenWidth/2 - 20, 0, 40, 40);

		//player1beginPosition = drawPlayerPosition(maps[mapNumber]);
		//player2beginPosition = drawPlayerPosition(maps[mapNumber]);
		player2beginPosition = myVector{400, 400};
		PlayerColider* colider1 = new PlayerColider(20);
		PlayerColider* colider2 = new PlayerColider(40, 40);
		player1 = new Player(player1beginPosition, 0.5, "../assets/jajo.png", maps[mapNumber].columns * TileSize, maps[mapNumber].rows * TileSize, colider1);
		player2 = new Player(player2beginPosition, 0.5, "../assets/draco.png", maps[mapNumber].columns * TileSize, maps[mapNumber].rows * TileSize, colider2);
	}

	return success;
}


bool Game::loadMedia() {
	bool success = true;

	/*brom = new GameObject("brom.png", 0, 200, 200, 200);
	if (brom == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}*/

	return success;
}

//void Game::beginYouuuuu() {
//	//SDL_Delay(1000);
//	
//	deltaTime = 0;
//	mapNumber++;
//
//	if (mapNumber == 1) {
//		map = Map{ 20, 16, ScreenWidth, ScreenHeight, TileSize, "../assets/mapFile2.txt" };
//	}
//	else if (mapNumber == 2) {
//		map = Map{ 20, 20, ScreenWidth, ScreenHeight, TileSize, "../assets/mapFile3.txt" };
//	}
//	else if (mapNumber >= 3) {
//		std::cout << "-------------------- KONIEC GRY ------------------- \n";
//		std::cout << " Statystyki \n";
//		std::cout << "Player1 wygral " << player1wins << " razy\n";
//		std::cout << "Player2 wygral " << player2wins << " razy\n";
//	}
//	
//	objectivePosition = map.getObjective();
//	maps[mapNumber] = map;
//	player1beginPosition = drawPlayerPosition(maps[mapNumber]);
//	player2beginPosition = drawPlayerPosition(maps[mapNumber]);
//	player1->setPosition(player1beginPosition);
//	player2->setPosition(player2beginPosition);
//	myVector movement = { 0, 0 };
//	player1->setMovement(movement);
//	player2->setMovement(movement);
//	directionPlayer1 = movement;
//	directionPlayer2 = movement;
//	player1->updateParameters(maps[mapNumber].columns * TileSize, maps[mapNumber].rows * TileSize);
//	player2->updateParameters(maps[mapNumber].columns * TileSize, maps[mapNumber].rows * TileSize);
//
//	SDL_Delay(1000);
//}

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color)
{
	//Renderer is set to draw in given color.
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	//And in those loops we draw a point in every pixel that belongs to the circle.
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			//It would be a filled square, if we wouldn't check if the point lies within the circle boundaries.
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}

bool Game::update() {
	bool quit = false;
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	frameTime = ((double)(NOW - LAST) / (double)10000000);

	

	while (SDL_PollEvent(&e) != 0)
	{
		// update keyboard state
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		
		if (state[SDL_SCANCODE_UP]) {
			directionPlayer1.setY(-1.0f);
		}
		else if (state[SDL_SCANCODE_DOWN]) {
			directionPlayer1.setY(1.0f);
		}
		else directionPlayer1.setY(0.0f);

		if (state[SDL_SCANCODE_RIGHT]) {
			directionPlayer1.setX(1.0f);
		}
		else if (state[SDL_SCANCODE_LEFT]) {
			directionPlayer1.setX(-1.0f);
		}
		else directionPlayer1.setX(0.0f);
		
		if (state[SDL_SCANCODE_SPACE]) {
			printf("Key pressed: SPACE!\n");
			if (jumpTime <= 0.1 && isOnGround)
			{
				//std::cout << "Jumping " << std::endl;
				isOnGround = false;
				jump_velocity = (2 * jumpHeight * 100) / distanceToPeak;
				gravity = (2 * jumpHeight * 100 * 100)
					/ (distanceToPeak * distanceToPeak);

				velY = -jump_velocity;
				/*std::cout << "HEIGHT: " << jumpHeight << std::endl;
				std::cout << "DISTANCE: " << distanceToPeak << std::endl;
				std::cout << "V0 : " << jump_velocity << std::endl;
				std::cout << "G: " << gravity << std::endl << std::endl;*/
				
			}
			break;
		}

		if (state[SDL_SCANCODE_O]) {
			if (mapSpeed1 + 0.1f < 1) {
				mapSpeed1 += 0.1f;
			}
			std::cout << "mapSpeed1 = " << mapSpeed1 << std::endl;
		}
		if (state[SDL_SCANCODE_P]) {
			if (mapSpeed1 - 0.1f > 0) {
				mapSpeed1 -= 0.1f;
			}
			std::cout << "mapSpeed1 = " << mapSpeed1 << std::endl;
		}

		if (state[SDL_SCANCODE_K]) {
			if (mapSpeed2 + 0.1f < 1) {
				mapSpeed2 += 0.1f;
			}
			std::cout << "mapSpeed2 = " << mapSpeed2 << std::endl;
			
		}
		if (state[SDL_SCANCODE_L]) {
			if (mapSpeed2 - 0.1f > 0) {
				mapSpeed2 -= 0.1f;
			}
			std::cout << "mapSpeed2 = " << mapSpeed2 << std::endl;
		}

		if (state[SDL_SCANCODE_N]) {
			if (mapSpeed3 + 0.1f < 1) {
				mapSpeed3 += 0.1f;
			}
			std::cout << "mapSpeed3 = " << mapSpeed3 << std::endl;

		}
		if (state[SDL_SCANCODE_M]) {
			if (mapSpeed3 - 0.1f > 0) {
				mapSpeed3 -= 0.1f;
			}
			std::cout << "mapSpeed3 = " << mapSpeed3 << std::endl;
		}

		if (!player2keyboardControl) {
			if (state[SDL_SCANCODE_W]) {
				directionPlayer2.setY(-1.0f);
			}
			else if (state[SDL_SCANCODE_S]) {
				directionPlayer2.setY(1.0f);
			}
			else directionPlayer2.setY(0.0f);

			if (state[SDL_SCANCODE_D]) {
				directionPlayer2.setX(1.0f);
			}
			else if (state[SDL_SCANCODE_A]) {
				directionPlayer2.setX(-1.0f);
			}
			else directionPlayer2.setX(0.0f);
		}
		
		if (SDL_GetMouseState(&mouseX, &mouseY)) {
			//std::cout << "Mouse X position: " << mouseX << "  |  Mouse Y position: " << mouseY << "\n";
		}
	}

	int scaledScreenWidth = (int)(ScreenWidth / scale);
	int scaledScreenHeight = (int)(ScreenHeight / scale);
	float maxScale = 1;

	// skalowanie obrazu
	SDL_RenderSetScale(gRenderer, scale, scale);

	// --------------------------- CAMERA -----------------------------------

	// camera track 1 player

	cameraRect.x = player2->getPosition().getX() - ScreenWidth / 2;
	cameraRect.y = player2->getPosition().getY() - 400;

	// camera stop tracking when comes to end of map
	if (cameraRect.x < 0) cameraRect.x = 0;
	if (cameraRect.y < 0) cameraRect.y = 0;
	
	if (cameraRect.x > maps[mapNumber].columns * TileSize - scaledScreenWidth) cameraRect.x = maps[mapNumber].columns * TileSize - scaledScreenWidth;
	if (cameraRect.y > maps[mapNumber].rows * TileSize - scaledScreenHeight) cameraRect.y = maps[mapNumber].rows * TileSize - scaledScreenHeight;

	// wczytywanie mapy w zale¿noœci od po³o¿enia kamery
	
	SDL_RenderClear(gRenderer);

	maps[3].drawMap(cameraRect.x * mapSpeed3, cameraRect.y, scale);
	maps[2].drawMap(cameraRect.x * mapSpeed2, cameraRect.y, scale);
	maps[1].drawMap(cameraRect.x * mapSpeed1, cameraRect.y, scale);
	maps[mapNumber].drawMap(cameraRect.x, cameraRect.y, scale);
	
	//player1->draw(cameraRect.x, cameraRect.y);
	player2->draw(cameraRect.x, cameraRect.y);

	
	if (!isOnGround) {
		velY += gravity * frameTime;
		player2Przemieszczenie = myVector(directionPlayer2.getX() * 0.5 * deltaTime, velY * frameTime + 0.5 * gravity * frameTime * frameTime);
		jumpTime += frameTime;
	}
	else {
		velY = 0;
		player2Przemieszczenie = myVector(directionPlayer2.getX() * 0.5 * deltaTime, 0.0);
		jumpTime = 0;
	}

	player2->update(player2Przemieszczenie, (float)deltaTime);
	
	if (player2->checkCollision(maps[mapNumber])) {
		isOnGround = true;
		jumpTime = 0;
	}
	else {
		isOnGround = false;
	}
	
	//player1->checkCollision(maps[mapNumber]);
	//player1->update(directionPlayer1, (float)deltaTime);

	SDL_RenderPresent(gRenderer);

	return quit;
}

void Game::close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	SDL_JoystickClose(gGameController);
	gGameController = NULL;

	IMG_Quit();
	SDL_Quit();
}