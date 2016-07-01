#!/bin/bash

if [ $# -eq0 ]
then
	echo "Erreur, argument manquant"
	exit 1

else 
	[[-z $(which libsdl1.2-dev)]] && sudo apt-get install libsdl1.2-dev && echo "Installation SDL...\n"
	gcc main.c -lSDL -o $@
	./$@

fi
