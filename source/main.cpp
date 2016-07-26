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
SDL_Renderer* r1;
SDL_Rect Background;

Background.x = 200;
Background.y = 200;
Background.h = 500;
Background.w = 500;

#if defined(_WIN32) || (WIN64) //this code is used to make sure this window that uses
							  //SDL runs on Windows properly
 cout << "Running on Windows :) "<<endl;
 cout << "Hopefully working on windows" <<endl;

 string currentWorkingDirectory(getcwd(NULL, 0));

 string images_dir = currentWorkingDirectory + "\\Resources\\images";

#endif

#if defined(__APPLE__)//this code is used to make sure this window that uses
	  	  	  	  	  //SDL runs on Apple properly

cout << "Running on Apple :) " <<endl;
string currentWorkingDirectory(getcwd(NULL, 0));

 string images_dir = currentWorkingDirectory + "/Resources/images/";
#endif


SDL_Window *window;
//initialize SDL
SDL_Init(SDL_INIT_VIDEO);
//Create the window
window = SDL_CreateWindow("SDL Test Window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1024,768,SDL_WINDOW_OPENGL);

//create a renderer
r1 = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

SDL_Surface *surface = IMG_Load((images_dir + "placeholder.png").c_str());

//create a texture

SDL_Texture * t1 = IMG_LoadTexture(r1, "placeholder.png");

//Creates a texture using the surface
t1 = SDL_CreateTextureFromSurface(r1,surface);

SDL_FreeSurface(surface);
if (t1 == NULL)
{
	cout << "Error Loading background :(" << endl;

}
if(window == NULL)
{
	printf("\n Couldn't create window :( ",SDL_GetError());
	return 1;
}

// clear buffer and draw agents and walls.
SDL_RenderCopy(r1, t1, NULL, &Background);

SDL_RenderPresent(r1);

SDL_Delay(3000);

SDL_RenderClear(r1);

SDL_DestroyWindow(window);

SDL_Quit();

return(0);
}
