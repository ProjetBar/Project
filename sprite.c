#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include "sprite.c"	

void sprite(void)
{	
	Client[ 0 ].x = 0;
    Client[ 0 ].y = 0;
    Client[ 0 ].w = SHEET_WIDTH/2;
    Client[ 0 ].h = SHEET_HEIGHT/2;
	
	Client[ 1 ].x = SHEET_WIDTH/2;
    Client[ 1 ].y = 0;
    Client[ 1 ].w = SHEET_WIDTH/2;
    Client[ 1 ].h = SHEET_HEIGHT/2;
 
    Client[ 2 ].x = 0;
    Client[ 2 ].y = SHEET_HEIGHT/2;
    Client[ 2 ].w = SHEET_WIDTH/2;
    Client[ 2 ].h = SHEET_HEIGHT/2;
 
    Client[ 3 ].x = SHEET_WIDTH/2;
    Client[ 3 ].y = SHEET_HEIGHT/2;
    Client[ 3 ].w = SHEET_WIDTH/2;
    Client[ 3 ].h = SHEET_HEIGHT/2;
}