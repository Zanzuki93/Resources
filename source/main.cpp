#if defined(_WIN32) || (WIN64)

#include "SDL.h"

#endif

#if defined(__APPLE__)

#include "SDL2/SDL.h"

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

#endif

#if defined(__APPLE__)//this code is used to make sure this window that uses
	  	  	  	  	  //SDL runs on Apple properly

cout << "Running on Apple :) " <<endl;

#endif


SDL_Window *window;

SDL_Init(SDL_INIT_VIDEO);

window = SDL_CreateWindow("SDL Test Window",SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_OPENGL);

if(window == NULL)
{
	printf("\n Couldn't create window :( ",SDL_GetError());
	return 1;
}
SDL_Delay(3000);

SDL_DestroyWindow(window);

SDL_Quit();

return(0);
}
