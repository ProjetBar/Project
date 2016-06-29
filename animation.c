#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include "bar.h"

void anime(SDL_Rect positionFond, SDL_Surface *ecran, SDL_Surface *imageDeFond,SDL_Rect position_Client,SDL_Surface *Client)
{
	
	positionFond.x = 0;
	positionFond.y = 0;
	position_Client.x = 800;
	position_Client.y = 553;
	int avanceX = 1, avanceY = 1;
	while (1)
	{
			/* On blitte par-dessus l'écran */
		SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
		SDL_BlitSurface(Client, NULL, ecran, &position_Client);
		
		/* a tester, deplacement du client  */
		
		if (avanceY) position_Client.y --;
		if (position_Client.y == 300) position_Client.y == 300;
			
		
		//SDL_BlitSurface(Client,)

		SDL_Flip(ecran);
		Close_SDL(imageDeFond);
		
	}
}

void Close_SDL(SDL_Surface *imageDeFond)
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
