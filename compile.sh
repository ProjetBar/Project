#!/bin/bash
if [ $@ -eq0 ]
then
	echo "Erreur, argument manquant"
	exit 1

else 
	gcc main.c -lSDL -o $@
	./$@

fi
