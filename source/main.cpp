#if defined(_WIN32) || (WIN64)

#include "SDL.h"

#include "SDL_image.h"

#endif

#if defined(_WIN32) || (_WIN64)
#include <direct.h>
#define getcwd _getcwd
#endif

#if defined(__APPLE__)

#include "SDL2/SDL.h"

#include "SDL2_image/SDL_image.h"

#include "SDL2_mixer/SDL_mixer.h"

#include "SDL2_ttf/SDL_ttf.h"

#endif

using namespace std;


#include <stdio.h>
#include <iostream>
int main(int argc, char* argv[])
{
#if defined(_WIN32) || (WIN64) //this code is used to make sure this window that uses
							  //SDL runs on Windows properly
 cout << "Running on Windows :) "<<endl;
 cout << "Hopefully working on windows" <<endl;

 string currentWorkingDirectory(getcwd(NULL, 0));

 string images_dir = currentWorkingDirectory + "\\Resources\\images\\";

#endif

#if defined(__APPLE__)//this code is used to make sure this window that uses
	  	  	  	  	  //SDL runs on Apple properly

cout << "Running on Apple :) " <<endl;
string currentWorkingDirectory(getcwd(NULL, 0));

 string images_dir = currentWorkingDirectory + "/Resources/images/";
#endif

 SDL_Renderer* r1;
 int playerHealth = 100;
 int ammoCount = 10;
 bool hasBlackKey = false, hasPinkKey = false, hasPurpleKey = false;
 bool inGame = true;
 SDL_Event event;

SDL_Window *window;
//initialize SDL
SDL_Init(SDL_INIT_VIDEO);
//Create the window
window = SDL_CreateWindow("SDL Test Window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1024,768,SDL_WINDOW_OPENGL);

//create a renderer
r1 = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//create the player texture
SDL_Rect Player;
Player.x = 750;
Player.y = 620;
Player.h = 50;
Player.w = 10;

const int Player_Vel = 5;

int PlayerVelX = 0;
int PlayerVelY = 0;

SDL_Texture * t2 = IMG_LoadTexture(r1,(images_dir+"TestImage.png").c_str());

//create the background texture
SDL_Rect Background;
SDL_Texture * t1 = IMG_LoadTexture(r1, (images_dir+"LevelDesign2D.png").c_str());

Background.x = 0;
Background.y = -1468;
int w,h;
SDL_QueryTexture(t1,NULL,NULL,&w,&h);
Background.h = h;
Background.w = w;
//Setting Up Walls
//Right Wall
SDL_Rect Wall;
Wall.x = 1220;
Wall.y = -620;
Wall.w = 30;
Wall.h = 1300;
SDL_Texture * w1 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());
//Left Wall
SDL_Rect Wall2;
Wall2.x = 0;
Wall2.y = -1270;
Wall2.w = 10;
Wall2.h = 1970;
SDL_Texture * w2 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());
//Roof
SDL_Rect Wall3;
Wall3.x = 0;
Wall3.y = -1270;
Wall3.w = 1650;
Wall3.h = 30;
SDL_Texture * w3 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());
//Floor
SDL_Rect Wall4;
Wall4.x = 0;
Wall4.y = 670;
Wall4.w = 1650;
Wall4.h = 30;
SDL_Texture * w4 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());
//Right Wall
SDL_Rect Wall5;
Wall5.x = 460;
Wall5.y = -790;
Wall5.w = 30;
Wall5.h = 1475;
SDL_Texture * w5 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());
//Right Wall
SDL_Rect Wall6;
Wall6.x = 1650;
Wall6.y = -1270;
Wall6.w = 10;
Wall6.h = 1970;
SDL_Texture * w6 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());
//Ceiling For Rooms
SDL_Rect Wall7;
Wall7.x = 0;
Wall7.y = -790;
Wall7.w = 40;
Wall7.h = 30;
SDL_Texture * w7 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());
SDL_Rect Wall8;
Wall8.x = 150;
Wall8.y = -790;
Wall8.w = 325;
Wall8.h = 20;
SDL_Texture * w8 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());
SDL_Rect Wall9;
Wall9.x = 650;
Wall9.y = -790;
Wall9.w = 1000;
Wall9.h = 20;
SDL_Texture * w9 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());
SDL_Rect Wall10;
Wall10.x = 990;
Wall10.y = -620;
Wall10.w = 500;
Wall10.h = 20;
SDL_Texture * w10 = IMG_LoadTexture(r1, (images_dir + "WallTexturePlaceholder.png").c_str());

//Creating a pickup
SDL_Rect healthPickUp;
healthPickUp.x = 700;
healthPickUp.y = 620;
healthPickUp.w = 30;
healthPickUp.h = 30;
SDL_Texture * HealthPkUp1 = IMG_LoadTexture(r1, (images_dir + "healthPickUp.png").c_str());
//Creating a ammo pickup
SDL_Rect ammoPickUp;
ammoPickUp.x = 600;
ammoPickUp.y = 620;
ammoPickUp.w = 30;
ammoPickUp.h = 30;
SDL_Texture * AmmoPkUp1 = IMG_LoadTexture(r1, (images_dir + "ammoPickUp.png").c_str());
//Creating the Health Bar
SDL_Rect HealthBarFront;
HealthBarFront.x = 100;
HealthBarFront.y = 50;
HealthBarFront.w = 200;
HealthBarFront.h = 30;
SDL_Texture * HBarFront = IMG_LoadTexture(r1, (images_dir + "healthBar.png").c_str());
SDL_Rect HealthBarBack;
HealthBarBack.x = 100;
HealthBarBack.y = 50;
HealthBarBack.w = 200;
HealthBarBack.h = 30;
SDL_Texture * HBarBack = IMG_LoadTexture(r1, (images_dir + "healthBarBackground.png").c_str());
//Burning Windmill
SDL_Rect Windmill;
Windmill.x = 53;
Windmill.y = 30;
Windmill.w = 50;
Windmill.h = 50;
SDL_Texture * WindmillTexture = IMG_LoadTexture(r1, (images_dir + "windmillGUI.png").c_str());
SDL_Rect Windmill2;
Windmill2.x = 290;
Windmill2.y = 30;
Windmill2.w = 50;
Windmill2.h = 50;
SDL_Texture * WindmillTexture2 = IMG_LoadTexture(r1, (images_dir + "windmillGUI.png").c_str());
//Creating the Mana Bar
SDL_Rect ManaBarFront;
ManaBarFront.x = 100;
ManaBarFront.y = 125;
ManaBarFront.w = 200;
ManaBarFront.h = 30;
SDL_Texture * MBarFront = IMG_LoadTexture(r1, (images_dir + "ammoGUI.png").c_str());
SDL_Rect ManaBarBack;
ManaBarBack.x = 100;
ManaBarBack.y = 125;
ManaBarBack.w = 200;
ManaBarBack.h = 30;
SDL_Texture * MBarBack = IMG_LoadTexture(r1, (images_dir + "ammoGUIBackground.png").c_str());
//Mana Potion GUI
SDL_Rect ManaPotion;
ManaPotion.x = 53;
ManaPotion.y = 110;
ManaPotion.w = 50;
ManaPotion.h = 50;
SDL_Texture * ManaPot = IMG_LoadTexture(r1, (images_dir + "manaPotionGUI.png").c_str());
//Creating the GUI For the Keys
SDL_Rect PinkKeyGUI;
PinkKeyGUI.x = 100;
PinkKeyGUI.y = 200;
PinkKeyGUI.w = 50;
PinkKeyGUI.h = 50;
SDL_Texture * PinkKeyGUITexture = IMG_LoadTexture(r1, (images_dir + "pinkKeyPickUp.png").c_str());
SDL_Rect PurpleKeyGUI;
PurpleKeyGUI.x = 150;
PurpleKeyGUI.y = 200;
PurpleKeyGUI.w = 50;
PurpleKeyGUI.h = 50;
SDL_Texture * PurpleKeyGUITexture = IMG_LoadTexture(r1, (images_dir + "purpleKeyPickUp.png").c_str());
SDL_Rect BlackKeyGUI;
BlackKeyGUI.x = 200;
BlackKeyGUI.y = 200;
BlackKeyGUI.w = 50;
BlackKeyGUI.h = 50;
SDL_Texture * BlackKeyGUITexture = IMG_LoadTexture(r1, (images_dir + "blackKeyPickUp.png").c_str());
//Creating the Keys 
SDL_Rect PinkKey;
PinkKey.x = 500;
PinkKey.y = 550;
PinkKey.w = 30;
PinkKey.h = 30;
SDL_Texture * PinkKeyTexture = IMG_LoadTexture(r1, (images_dir + "pinkKeyPickUp.png").c_str());
SDL_Rect PurpleKey;
PurpleKey.x = 700;
PurpleKey.y = 550;
PurpleKey.w = 30;
PurpleKey.h = 30;
SDL_Texture * PurpleKeyTexture = IMG_LoadTexture(r1, (images_dir + "purpleKeyPickUp.png").c_str());
SDL_Rect BlackKey;
BlackKey.x = 600;
BlackKey.y = 550;
BlackKey.w = 30;
BlackKey.h = 30;
SDL_Texture * BlackKeyTexture = IMG_LoadTexture(r1, (images_dir + "blackKeyPickUp.png").c_str());
//Creating a Enemy 
SDL_Rect Enemy;
Enemy.x = 500;
Enemy.y = 620;
Enemy.w = 20;
Enemy.h = 30;
SDL_Texture * EnemyTexture = IMG_LoadTexture(r1, (images_dir + "placeholder.png").c_str());



//Error Messages For Texture File Paths
if (t1 == NULL)
{
	//used to check to see if the background image is working
	cout << "Error Loading Background :(" << endl;
}
if(t2 == NULL)
{
	cout <<"Error Loading Player :("<<endl;
}

if(window == NULL)
{
	printf("\n Couldn't create window :( ",SDL_GetError());
	return 1;
}
while(inGame)
{
	//Input for Game//
	while(SDL_PollEvent(&event)!= 0)
	{
	if(event.type == SDL_QUIT)
	 {
	 inGame = false;

	 }
	else
	 {
		  if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
		  {

			  switch(event.key.keysym.sym)
			  {
				 case SDLK_ESCAPE:
				 inGame = false;
				 break;
				 case SDLK_w:
				 PlayerVelY -= Player_Vel;
				 break;
				 case SDLK_s:
				 PlayerVelY += Player_Vel;
				 break;
				 case SDLK_a:
				 PlayerVelX -= Player_Vel;
				 break;
				 case SDLK_d:
				 PlayerVelX += Player_Vel;
				 break;
				 /*case SDLK_p:
				 ManaBarFront.w -= 20;
				 ammoCount -= 1;
				 break;*/
			  }
		  }
		  else if(event.type == SDL_KEYUP && event.key.repeat == 0)
		  {
			  switch(event.key.keysym.sym)
			  {
				 case SDLK_w:
				 PlayerVelY += Player_Vel;
				 break;
				 case SDLK_s:
				 PlayerVelY -= Player_Vel;
				 break;
				 case SDLK_a:
				 PlayerVelX += Player_Vel;
				 break;
				 case SDLK_d:
				 PlayerVelX -= Player_Vel;
				 break;
			}
		 }
	  }
	}
	//Input End//

	//Update Player//
	//Adjusting the screen Horizontally
	Player.x += PlayerVelX;
	Player.y += PlayerVelY;
	if(Player.x > 1024 - (Player.w * 2))
		{
			Player.x = 1024 - (Player.w*2);
			Background.x -= PlayerVelX;

			Wall.x -= PlayerVelX;
			Wall2.x -= PlayerVelX;
			Wall3.x -= PlayerVelX;
			Wall4.x -= PlayerVelX;
			Wall5.x -= PlayerVelX;
			Wall6.x -= PlayerVelX;
			Wall7.x -= PlayerVelX;
			Wall8.x -= PlayerVelX;
			Wall9.x -= PlayerVelX;
			Wall10.x -= PlayerVelX;
			healthPickUp.x -= PlayerVelX;
			ammoPickUp.x -= PlayerVelX;
			Enemy.x -= PlayerVelX;
		}
	if(Player.x < 0 + (Player.w * 2))
			{
				Player.x = 0 + (Player.w*2);
				Background.x -= PlayerVelX;

				Wall.x -= PlayerVelX;
				Wall2.x -= PlayerVelX;
				Wall3.x -= PlayerVelX;
				Wall4.x -= PlayerVelX;
				Wall5.x -= PlayerVelX;
				Wall6.x -= PlayerVelX;
				Wall7.x -= PlayerVelX;
				Wall8.x -= PlayerVelX;
				Wall9.x -= PlayerVelX;
				Wall10.x -= PlayerVelX;
				healthPickUp.x -= PlayerVelX;
				ammoPickUp.x -= PlayerVelX;
				Enemy.x -= PlayerVelX;
			}
	//Checking For collision with walls and the player Left and Right
	if (SDL_HasIntersection(&Player, &Wall) || SDL_HasIntersection(&Player, &Wall2) ||
		SDL_HasIntersection(&Player, &Wall3) || SDL_HasIntersection(&Player, &Wall4)||
		SDL_HasIntersection(&Player, &Wall5) ||SDL_HasIntersection(&Player, &Wall6)||
		SDL_HasIntersection(&Player, &Wall7)||SDL_HasIntersection(&Player, &Wall8)||
		SDL_HasIntersection(&Player, &Wall9)||SDL_HasIntersection(&Player, &Wall10))
	{
		Player.x -= PlayerVelX;
	}
	//Enemy Collision
	/*if (SDL_HasIntersection(&Player, &Enemy))
	{
		Player.x -= PlayerVelX;
		HealthBarFront.w -= 10;
		playerHealth -= 5;
	}*/
	//Key Collision
	/*
	if (SDL_HasIntersection(&Player, &PinkKey))
	{
		Player.x -= PlayerVelX;
		PinkKey.x = 0;
		PinkKey.y = 0;
		hasPinkKey = true;
	}
	if (SDL_HasIntersection(&Player, &PurpleKey))
	{
		Player.x -= PlayerVelX;
		PurpleKey.x = 0;
		PurpleKey.y = 0;
		hasPurpleKey = true;
	}
	//Health PickUp Collision
	if (SDL_HasIntersection(&Player, &healthPickUp) && playerHealth < 100)
	{
		Player.x -= PlayerVelX;
		HealthBarFront.w += 10;
		playerHealth += 5;
	}
	if (playerHealth >= 100)
	{
		playerHealth = 100;
		HealthBarFront.w = 200;
	}
	if (playerHealth <= 0)
	{
		playerHealth = 0;
		HealthBarFront.w = 0;
	}
	//Mana PickUp Collision
	if (SDL_HasIntersection(&Player, &ammoPickUp) && ammoCount < 10)
	{
		Player.x -= PlayerVelX;
		ManaBarFront.w += 20;
		ammoCount += 1;
	}
	if (ammoCount >= 10)
	{
		ammoCount = 10;
		ManaBarFront.w = 200;
	}
	if (ammoCount <= 0)
	{
		ammoCount = 0;
		ManaBarFront.w = 0;
	}*/

	//Adjusting the screen Vertically
	if (Player.y < 0 + (Player.h * 2))
	{
		Player.y = 0 + (Player.h * 2);
		Background.y -= PlayerVelY;

		Wall.y -= PlayerVelY;
		Wall2.y -= PlayerVelY;
		Wall3.y -= PlayerVelY;
		Wall4.y -= PlayerVelY;
		Wall5.y -= PlayerVelY;
		Wall6.y -= PlayerVelY;
		Wall7.y -= PlayerVelY;
		Wall8.y -= PlayerVelY;
		Wall9.y -= PlayerVelY;
		Wall10.y -= PlayerVelY;
		healthPickUp.y -= PlayerVelY;
		ammoPickUp.y -= PlayerVelY;
		Enemy.y -= PlayerVelY;
	}

	if(Player.y > 768 - (Player.h * 2))
	{
		Player.y = 768 - (Player.h * 2);
		Background.y -= PlayerVelY;

		Wall.y -= PlayerVelY;
		Wall2.y -= PlayerVelY;
		Wall3.y -= PlayerVelY;
		Wall4.y -= PlayerVelY;
		Wall5.y -= PlayerVelY;
		Wall6.y -= PlayerVelY;
		Wall7.y -= PlayerVelY;
		Wall8.y -= PlayerVelY;
		Wall9.y -= PlayerVelY;
		Wall10.y -= PlayerVelY;
		healthPickUp.y -= PlayerVelY;
		ammoPickUp.y -= PlayerVelY;
		Enemy.y -= PlayerVelY;
	}


	////Checking For collision with walls Up and Down
	if (SDL_HasIntersection(&Player, &Wall) || SDL_HasIntersection(&Player, &Wall2) ||
		SDL_HasIntersection(&Player, &Wall3)|| SDL_HasIntersection(&Player, &Wall4)||
		SDL_HasIntersection(&Player,&Wall5) || SDL_HasIntersection(&Player, &Wall6)||
		SDL_HasIntersection(&Player, &Wall7)||SDL_HasIntersection(&Player, &Wall8)||
		SDL_HasIntersection(&Player, &Wall9)||SDL_HasIntersection(&Player, &Wall10))
	{
		Player.y -= PlayerVelY;
	}
	//Enemy Collision
	/*if (SDL_HasIntersection(&Player, &Enemy))
	{
		Player.y -= PlayerVelY;
		HealthBarFront.w -= 10;
		playerHealth -= 5;
	}*/
	//Key Collision
	/*if (SDL_HasIntersection(&Player, &BlackKey) && hasBlackKey != true)
	{
		Player.y -= PlayerVelY;
		BlackKey.x = 0;
		BlackKey.y = 0;
		hasBlackKey = true;
	}
	if (SDL_HasIntersection(&Player, &PinkKey) && hasPinkKey != true)
	{
		Player.y -= PlayerVelY;
		PinkKey.x = 0;
		PinkKey.y = 0;
		hasPinkKey = true;
	}
	if (SDL_HasIntersection(&Player, &PurpleKey) && hasPurpleKey != true)
	{
		Player.y -= PlayerVelY;
		PurpleKey.x = 0;
		PurpleKey.y = 0;
		hasPurpleKey = true;
	}
	//Health PickUp Collision
	if (SDL_HasIntersection(&Player, &healthPickUp))
	{
		Player.y -= PlayerVelY;
		HealthBarFront.w += 20;
		playerHealth += 10;
	}
	//Mana PickUp Collision
	if (SDL_HasIntersection(&Player, &ammoPickUp))
	{
		Player.y -= PlayerVelY;
		ManaBarFront.w += 20;
		ammoCount += 1;
	}*/
	//Update Player End//

//SDL Drawing Process//
// clear buffer and draw agents and walls.
SDL_RenderClear(r1);
//render a copy of the texture
SDL_RenderCopy(r1, t1, NULL, &Background);
//render what is presently in the buffer
SDL_RenderCopy(r1,t2,NULL,&Player);

//SDL_RenderCopy(r1, HealthPkUp1, NULL, &healthPickUp);
//Rendering the Ammo Pickup
//SDL_RenderCopy(r1, AmmoPkUp1, NULL, &ammoPickUp);
//Rendering the Health Bar
//SDL_RenderCopy(r1, HBarBack, NULL, &HealthBarBack);
//SDL_RenderCopy(r1, HBarFront, NULL, &HealthBarFront);
//SDL_RenderCopy(r1, WindmillTexture, NULL, &Windmill);
//SDL_RenderCopy(r1, WindmillTexture2, NULL, &Windmill2);
//Rendering the Ammo GUI
//SDL_RenderCopy(r1, MBarBack, NULL, &ManaBarBack);
//SDL_RenderCopy(r1, MBarFront, NULL, &ManaBarFront);
//SDL_RenderCopy(r1, ManaPot, NULL, &ManaPotion);
////Rendering the enemy texture
//SDL_RenderCopy(r1, EnemyTexture, NULL, &Enemy);
//Rendering the Keys in the level
/*if (hasPinkKey != true)
{
	SDL_RenderCopy(r1, PinkKeyTexture, NULL, &PinkKey);
}*/
/*if (hasBlackKey != true)
{
	SDL_RenderCopy(r1, BlackKeyTexture, NULL, &BlackKey);
}*/
/*if (hasPurpleKey != true)
{
	SDL_RenderCopy(r1, PurpleKeyTexture, NULL, &PurpleKey);
}*/
//Rendering the Keys for the GUI
/*if (hasPinkKey == true)
{*/
	/*SDL_RenderCopy(r1, PinkKeyGUITexture, NULL, &PinkKeyGUI);*/
/*}*/
/*if (hasBlackKey == true)
{*/
	/*SDL_RenderCopy(r1, BlackKeyGUITexture, NULL, &BlackKeyGUI);*/
/*}*/
/*if (hasPurpleKey == true)
{*/
	/*SDL_RenderCopy(r1, PurpleKeyGUITexture, NULL, &PurpleKeyGUI);*/
/*}*/

//Wall Texture Code
SDL_RenderCopy(r1,w1,NULL,&Wall);

SDL_RenderCopy(r1,w2,NULL,&Wall2);

SDL_RenderCopy(r1,w3,NULL,&Wall3);

SDL_RenderCopy(r1, w4, NULL, &Wall4);

SDL_RenderCopy(r1, w5, NULL, &Wall5);

SDL_RenderCopy(r1, w6, NULL, &Wall6);

SDL_RenderCopy(r1, w7, NULL, &Wall7);

SDL_RenderCopy(r1, w8, NULL, &Wall8);

SDL_RenderCopy(r1, w9, NULL, &Wall9);

SDL_RenderCopy(r1, w10, NULL, &Wall10);

SDL_RenderPresent(r1);
//SDL Drawing Process End//
SDL_Delay(16);
}
//End of Game Loop//
SDL_DestroyWindow(window);

SDL_Quit();

return(0);
}
