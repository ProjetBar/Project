#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include "bar.h"

void Menu (void)
{
    SDL_Surface *ecran_menu = NULL, *image_Menu= NULL, *image_biere = NULL;
    SDL_Rect positionMenu,positionBiere;
SDL_Event event;
    positionMenu.x = 0;
    positionMenu.y = 0;
    positionBiere.x = 0;
    positionBiere.y = 0;

    SDL_Init(SDL_INIT_VIDEO);
	SDL_ShowCursor(SDL_DISABLE);
    ecran_menu = SDL_SetVideoMode(960, 550, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Projet Bar Menu", NULL);

    image_Menu = SDL_LoadBMP("MenuBar.bmp");
    image_biere = SDL_LoadBMP("bouteille.bmp");
	while (1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                SDL_Quit();
   		SDL_FreeSurface(image_biere);
		exit(0);
                break;
            case SDL_MOUSEMOTION:
		positionBiere.x = event.motion.x;
           	 positionBiere.y = event.motion.y;
		break;

	    case SDL_MOUSEBUTTONUP:
        	if (event.motion.x >= 220 && event.motion.x <= 500 && event.motion.y >=200 && event.motion.x <= 500 )
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				init_SDL();
			}	
		}
	   
         }
                
	SDL_SetColorKey(image_biere,SDL_SRCCOLORKEY,SDL_MapRGB(image_biere->format, 0,0,0));
	SDL_BlitSurface(image_Menu, NULL, ecran_menu, &positionMenu);
        SDL_BlitSurface(image_biere, NULL, ecran_menu, &positionBiere);
        SDL_Flip(ecran_menu);

    }

       
}


