#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include "sprite.c"

void init_SDL (void)
{
	SDL_Init(SDL_INIT_VIDEO);
	ecran = SDL_SetVideoMode(984, 553, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("Project Bar", NULL);
	imageDeFond = SDL_LoadBMP("Bar.bmp");
	imageClient = SDL_LoadBMP("Client.bmp");
	
}

void Close_SDL(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{

		switch (event.type)
		{
			case SDL_QUIT:
				SDL_FreeSurface(imageDeFond); /* On libère la surface */
				SDL_Quit();
				exit(0);
				break;
		}
	}
}

void anime(void)
{
	SDL_Surface *ecran = NULL, *imageDeFond = NULL;
	SDL_Surface *Client[4] = NULL, *Barman[4] = NULL;
	int avanceX = 1, avanceY = 1;

	SDL_Rect position_Client; //position du client
	SDL_Rect position_Barman;	// position du barman
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	position_Client.x = 0;
	position_Client.y = 0;

	while (1)
	{
			/* On blitte par-dessus l'écran */
		SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
		SDL_BlitSurface(Client, NULL, ecran, &position_Client);
		
		/* a tester, deplacement du client */
		if (avanceX) position_Client.x ++;
		else position_Client--;
		if (avanceY) position_Client.y ++;
		else position_Client.y--;
		
		//SDL_BlitSurface(Client,)

		SDL_Flip(ecran);
		Close_SDL();
		
	}


}
int main(int argc, char *argv[])
{
	init_SDL();
	anime();
return 0;
}