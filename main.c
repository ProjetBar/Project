#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include "bar.h"

void init_SDL (void)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *ecran = NULL, *imageDeFond = NULL;
	SDL_Surface *Client = NULL;
	SDL_Rect position_Client; //position du client
	SDL_Rect position_Barman;	// position du barman
	SDL_Rect positionFond;
	ecran = SDL_SetVideoMode(984, 553, 32, SDL_HWSURFACE);
	int avanceX = 1, avanceY = 1;
	SDL_WM_SetCaption("Project Bar", NULL);
	imageDeFond = SDL_LoadBMP("Bar.bmp");
	Client = SDL_LoadBMP("client.bmp");
//	imageClient = SDL_LoadBMP("Client.bmp");
	anime(positionFond, ecran, imageDeFond,position_Client,Client);
}


int main(int argc, char *argv[])
{
	init_SDL();
return 0;
}
