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
Player.x = 500;
Player.y = 400;
Player.h = 10;
Player.w = 10;

const int Player_Vel = 5;

int PlayerVelX = 0;
int PlayerVelY = 0;

SDL_Texture * t2 = IMG_LoadTexture(r1,(images_dir+"TestImage.png").c_str());

//create the background texture
SDL_Rect Background;
SDL_Texture * t1 = IMG_LoadTexture(r1, (images_dir+"LevelDesignWIP.png").c_str());

Background.x = 0;
Background.y = -768;
int w,h;
SDL_QueryTexture(t1,NULL,NULL,&w,&h);
Background.h = h;
Background.w = w;

//Setting Up the Walls
/*SDL_Rect Wall;
Wall.x = 975;
Wall.y = 0;
Wall.w = 2049;
Wall.h = 1536;
//SDL_Texture * w1 = IMG_LoadTexture(r1, (images_dir+"WallTexturePlaceholder.png").c_str());
SDL_Rect Wall2;
Wall2.x = 0;
Wall2.y = -768;
Wall2.w = 40;
Wall2.h = 1536;
//SDL_Texture * w2 = IMG_LoadTexture(r1, (images_dir+"WallTexturePlaceholder.png").c_str());
SDL_Rect Wall3;
Wall3.x = 40;
Wall3.y = 0;
Wall3.w = 2049;
Wall3.h = 40;
//SDL_Texture * w3 = IMG_LoadTexture(r1, (images_dir+"WallTexturePlaceholder.png").c_str());
SDL_Rect Wall4;
Wall4.x = 40;
Wall4.y = 728;
Wall4.w = 1025;
Wall4.h = 40;
//SDL_Texture * w4 = IMG_LoadTexture(r1, (images_dir+"WallTexturePlaceholder.png").c_str());
*/
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

			/*Wall.x -= PlayerVelX;
			Wall2.x -= PlayerVelX;
			Wall3.x -= PlayerVelX;
			Wall4.x -= PlayerVelX;*/
		}
	if(Player.x < 0 + (Player.w * 2))
			{
				Player.x = 0 + (Player.w*2);
				Background.x -= PlayerVelX;

				/*Wall.x -= PlayerVelX;
				Wall2.x -= PlayerVelX;
				Wall3.x -= PlayerVelX;
				Wall4.x -= PlayerVelX;*/
			}
	//Checking For collision with walls and the player Left and Right
		/*if(SDL_HasIntersection(&Player,&Wall) ||SDL_HasIntersection(&Player,&Wall2) ||
				SDL_HasIntersection(&Player,&Wall3) || SDL_HasIntersection(&Player,&Wall4))*/
	//Adjusting the screen Vertically
	//Player.y += PlayerVelY;
	if(Player.y > 768 - (Player.h * 2))
			{
				Player.y = 768 - (Player.h*2);
				Background.y -= PlayerVelY;

				/*Wall.y -= PlayerVelY;
				Wall2.y -= PlayerVelY;
				Wall3.y -= PlayerVelY;
				Wall4.y -= PlayerVelY;*/
			}
		if(Player.y < 0 + (Player.h * 2))
				{
					Player.y = 0 + (Player.h*2);
					Background.y -= PlayerVelY;

					/*Wall.y -= PlayerVelY;
					Wall2.y -= PlayerVelY;
					Wall3.y -= PlayerVelY;
					Wall4.y -= PlayerVelY;*/
				}

	//Checking For collision with walls Up and Down
	/*if(SDL_HasIntersection(&Player,&Wall) ||SDL_HasIntersection(&Player,&Wall2) ||
				SDL_HasIntersection(&Player,&Wall3) || SDL_HasIntersection(&Player,&Wall4))*/



	//Update Player End//

//SDL Drawing Process//
// clear buffer and draw agents and walls.
SDL_RenderClear(r1);
//render a copy of the texture
SDL_RenderCopy(r1, t1, NULL, &Background);
//render what is presently in the buffer
SDL_RenderCopy(r1,t2,NULL,&Player);

//Wall Texture Code
/*SDL_RenderCopy(r1,w1,NULL,&Wall);

SDL_RenderCopy(r1,w2,NULL,&Wall2);

SDL_RenderCopy(r1,w3,NULL,&Wall3);

SDL_RenderCopy(r1,w4,NULL,&Wall4);*/

SDL_RenderPresent(r1);
//SDL Drawing Process End//
SDL_Delay(16);
}
//End of Game Loop//
SDL_DestroyWindow(window);

SDL_Quit();

return(0);
}
