#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#define CMAX 32 
#define TMAX 20 

/* définition des structures */ 
typedef struct catalogue { 
	char refvehicule[CMAX]; 
	int refpiece[TMAX]; 
	int dateval[TMAX]; 
	struct catalogue *suiv; 
} T_CAT; 


/* Déclaration des prototypes fonctions */ 
T_CAT* creeCat(void); 
T_CAT* insBP(T_CAT* Liste, T_CAT* Mail); 
void afficheCat(T_CAT* Liste); 
void afficheUnEltCat(T_CAT* M); // En plus par rapport à l'énoncé 
T_CAT* rechRefVe(T_CAT* Liste, char* Laquelle); 
int rechRefPiece(T_CAT* Liste, char* vehicule, int dateMiseEnService); 
void sauvCat(T_CAT* Liste); 
T_CAT* lireFicCreerUnCat(FILE *fic); 
T_CAT* lireFicCreerListeCat(T_CAT* Liste);
T_CAT* suppRefVe(T_CAT* Liste, char* Laquelle); 
void desalloc(T_CAT* Liste); 
void affRefPiece(T_CAT* Liste, int iPiece); 

char menu(void) 
{ 
	char cChoix; 
/* affichage du menu, demande choix, retourne le choix */ 
		printf("\n-------- MENU DE CHOIX -------\n"); 
		printf("(1) - Saisir une nouvelle référence\n"); 
		printf("(2) - Afficher le catalogue\n"); 
		printf("(3) - Rechercher un véhicule\n"); 
		printf("(4) - Rechercher une pièce (pour un véhicule)\n"); 
		printf("(5) - Sauvegarder le catalogue\n"); 
		printf("(6) - Récupérer un catalogue\n");
		printf("(7) - Supprimer un véhicule\n"); 
		printf("(8) - Afficher l'utilisation de la pièce\n"); 
		printf("(9) - Quitter...\n"); 
		printf("-------------------------------\n"); 
		printf("\nDonnez votre choix : "); 
		scanf(" %c", &cChoix); 
		return cChoix; 
} /* fin menu */

int main(void) 
{ 
	T_CAT *Liste= NULL, *Mail=NULL, *MailTrouve = NULL; 
	char iChoix = 0; 
	char sChaine[CMAX]; 
	int iDate = 0, iTrouve = 0; 
	int iPiece = 0; 

	do { 
	iChoix = menu(); 
	switch (iChoix) 
		{ 
		case '1' : /* saisie de la nouvelle référence */ 
			Mail = creeCat(); 
			Liste = insBP(Liste, Mail);
			break; 
		case '2' : /* affichage du catalogue */ 
			afficheCat(Liste); 
		break; 
		case '3' : /* recherche d'un véhicule */ 
			printf("\nDonner la référence du véhicule à rechercher : "); 
			scanf(" %s",sChaine); 
			MailTrouve = rechRefVe(Liste, sChaine); 
			printf("\n*************************************************************\n"); 
			afficheUnEltCat(MailTrouve); 
			break; 
		case '4' : /* recherche d'une pièce pour un véhicule */ 
			printf("\nDonner la référence du véhicule (pour la pièce à rechercher : "); 
			scanf(" %s",sChaine); 
			printf("\nDonner la date de mise en service du véhicule : "); 
			scanf(" %d",&iDate);
			iTrouve = rechRefPiece(Liste, sChaine, iDate); 
			printf("\nRéférence trouvée (-1 mauvaise ref vehicule, -2 mauvaises dates) : %d",  iTrouve); 
			break; 
		case '5' : /* enregistrement de la liste dans un fichier */ 
			sauvCat(Liste); 
			break; 
		case '6' : /* récupération de la liste depuis un fichier */ 
			printf("\nAttention la liste en cours va être supprimée avant la récupération"); 
			desalloc(Liste); 
			Liste = NULL; 
			Liste = lireFicCreerListeCat(Liste); 
			break; 
		case '7' : /* suppression d'un véhicule */
			printf("\nDonner la référence du véhicule à supprimer : "); 
			scanf(" %s",sChaine); 
			Liste = suppRefVe(Liste, sChaine); 
			break; 
		case '8' : /* recherche des véhicules utilisant une pièce */ 
			printf("\nDonner la référence de la pièce : "); 
			scanf(" %d",&iPiece); 
			affRefPiece(Liste, iPiece); 
			break; 
		case '9' : /* sortie du programme */ 
			printf("Vous avez choisi de quitter le programme.\n"); 
			printf("Tapez sur une touche pour continuer...\n\n"); 
			getchar(); 
			break; 
		default : 
			printf("\nMauvais choix, essayez à nouveau.\n"); 
		} 
	} while(iChoix!= '9'); 
	return 0; 
} /* fin main() */

T_CAT* creeCat(void) 
{ 
	T_CAT *ST_New = NULL;
	int iPiece = 0, iDate = 0; 
	int iTab = 0, iFin = 0; 

	ST_New = (T_CAT *)malloc(sizeof(T_CAT)); 
	if (ST_New == NULL) 
	{ 
		printf("\nErreur allocation memoire"); 
		return NULL; 
	}
	printf("\nSaisie de la référence du véhicule : "); 
	scanf("%s", ST_New->refvehicule); 
	
	printf("\nSaisie des pièces et des dates, donner la valeur -1 pour arrêter la saisie"); 
	while((iPiece != -1) && (iTab < TMAX)) 
	{ 
		printf("\nSaisir la %d référence de pièce, suivie de sa date de mise en service au format 136 AAAAMM:\n",iTab+1); 
		if (2 == scanf(" %d %d", &iPiece, &iDate)) 
		{ 
			if ((iPiece == -1) || (iDate == -1)) 
			{ 
					iFin = iTab;
					iTab = TMAX;
			} 
			else 
			{ 
				ST_New->refpiece[iTab] = iPiece; 
				ST_New->dateval[iTab] = iDate; 
				iTab++; 
			} 
		}
		else 
		{ 
			printf("\nErreur de saisie, sortie de la fonction"); 
			iFin = iTab; 
			iTab = TMAX; 
		} 

	}
	
	for(iTab = iFin; iTab < TMAX; iTab++) 
	{ 
		ST_New->refpiece[iTab] = -1; 
		ST_New->dateval[iTab] = -1; 
	} 
	ST_New->suiv = NULL; 
	return ST_New; 
} /* fin CreeCat */

T_CAT* insBP(T_CAT* ST_Liste, T_CAT* ST_New_Mail) 
{ 
	if (ST_Liste == NULL) 
		return ST_New_Mail; 
	if (ST_New_Mail == NULL) 
		return ST_Liste; 
	if (strcmp(ST_New_Mail->refvehicule, ST_Liste->refvehicule) == 0) 
	{ 
		printf("\n Cette référence de véhicule existe déjà, annulation de l'insertion"); 
		free(ST_New_Mail); 
		ST_New_Mail = NULL; 
		return ST_Liste; 
	} 
	if (strcmp(ST_New_Mail->refvehicule, ST_Liste->refvehicule) < 0) 
	{ 
		ST_New_Mail->suiv = ST_Liste; 
		return ST_New_Mail; 
	} 
	else 
	{ 
		ST_Liste->suiv = insBP(ST_Liste->suiv,ST_New_Mail); 
		return ST_Liste; 
	} 
} /* fin insBP */

void afficheUnEltCat(T_CAT* ST_Liste) 
{
	int iTab; 
	if (ST_Liste != NULL) 
	{ 
		for(iTab = 0; ( ST_Liste->refpiece[iTab] != -1 ) && ( iTab < TMAX ); iTab++) 
		{ 
			printf("%21s*", ST_Liste->refvehicule); 
			printf("%18d*", ST_Liste->refpiece[iTab]); 
			printf("%19d*", ST_Liste->dateval[iTab]); 
			printf("\n"); 
		} 
	} 
} /* fin afficheUnEltCat */
void afficheCat(T_CAT* ST_Liste) 
{ 
	printf("\nRéférence Véhicule * N°Pièce * Mise en service*"); 
	printf("\n*************************************************************\n"); 
	while(ST_Liste != NULL) 
	{ 
		afficheUnEltCat(ST_Liste); 
		ST_Liste = ST_Liste->suiv; 
		printf("\n*************************************************************\n"); 
		
	} 
	printf("\n*************************************************************\n"); 
} /* fin afficheCat */ 


T_CAT* rechRefVe(T_CAT* ST_Liste, char* Laquelle) 
{ 
	while((ST_Liste != NULL) && strcmp(Laquelle, ST_Liste->refvehicule) != 0) 
	{ 
		ST_Liste = ST_Liste->suiv; 
	} 
	if (ST_Liste == NULL) 
	{ 
		printf("\nRéférence de véhicule inconnue dans la liste, consultez le catalogue"); 
		return NULL; 
	} 
	else 
	{ 
		printf("\nRéférence du véhicule trouvée");
		return ST_Liste; 
} 
} /* fin rechRefVe */

int rechRefPiece(T_CAT* ST_Liste, char* sVeh, int iDate) 
{ 
	int iTab; 
	T_CAT TEMP; 
	while((ST_Liste != NULL) && strcmp(sVeh, ST_Liste->refvehicule) != 0) 
	{ 
		ST_Liste = ST_Liste->suiv; 
	} 
	if (ST_Liste == NULL) 
	{ 
		printf("\nRéférence de véhicule inconnue dans la liste, consultez le catalogue"); 
		return -1; 
	} 
	else 
	{ 
		TEMP = *ST_Liste; 
		for(iTab = 0; (iTab < TMAX-1 ) && (TEMP.refpiece[iTab] != -1); iTab++) 
		{ 
			if((TEMP.dateval[iTab] <= iDate) && (iDate < TEMP.dateval[iTab+1])) 
				return TEMP.refpiece[iTab]; 
			if((TEMP.dateval[iTab] <= iDate) && (TEMP.dateval[iTab+1] == -1)) 
				return TEMP.refpiece[iTab]; 
		} 
		return -2; 
} 
} /* fin rechRefPiece */

void sauvCat(T_CAT* ST_Liste) 
{ 
	FILE *fic = NULL; 
	char sNomFic[CMAX]; 

	printf("\nDonnez le nom du fichier à créer (attention son contenu sera effacé) : "); 
	scanf(" %s", sNomFic);
	if ((fic = fopen(sNomFic, "wb")) == NULL) 
		printf("\nErreur d'ouverture de fichier - Abandon");
	else 
	{ 
		while(ST_Liste != NULL) 
		{ 
			if (fwrite(ST_Liste, sizeof( T_CAT), 1, fic) != 1) 
			{
				printf("\nErreur d'écriture dans le fichier - Abandon"); 
				ST_Liste = NULL; 
			} 
			else 
				ST_Liste = ST_Liste->suiv; 
		} 
		if ((fic != NULL) && (fclose(fic) != 0)) 
		printf("\nProblème de fermeture de fichier"); 
	} 
} /* fin sauvCat */

T_CAT* lireFicCreerUnCat(FILE *fic) 
{ 
	T_CAT ST_Temp, *ST_New = NULL; 

	memset(&ST_Temp,0, sizeof(T_CAT)); 
	if((feof(fic) == 0) && (fread(&ST_Temp, sizeof(T_CAT), 1, fic) == 1)) 
	{ 
		ST_New = (T_CAT *)malloc(sizeof(T_CAT)); 
		if (ST_New == NULL) 
		{ 
			printf("\nErreur allocation memoire"); 
			return NULL; 
		} 
		*ST_New = ST_Temp; 
		ST_New->suiv = NULL; 
		return ST_New; 
	} 
	return NULL; 
} /* fin lireFicCreerUnCat */


T_CAT* lireFicCreerListeCat(T_CAT* ST_Liste)
{ 
	FILE *fic = NULL;
	char sNomFic[CMAX]; 
	T_CAT *ST_Mail = NULL; 

	printf("\nDonnez le nom du fichier à récupérer : "); 
	scanf(" %s", sNomFic); 
	if ((fic = fopen(sNomFic, "rb")) == NULL) 
	{ 
		printf("\nErreur d'ouverture de fichier - Abandon"); 
		return NULL; 
	} 
	else 
	{ 
		ST_Mail = lireFicCreerUnCat(fic); 
		while( ST_Mail != NULL) 
		{ 
			ST_Liste = insBP(ST_Liste, ST_Mail); 
			ST_Mail = lireFicCreerUnCat(fic); 
		} 
		fclose(fic); 
	} 
	return ST_Liste; 
} /* fin lireFicCreerListeCat */

T_CAT* suppRefVe(T_CAT* ST_Liste, char* Laquelle) 
{ T_CAT* ST_Rem; 
		if (ST_Liste == NULL) 
		{ 
			printf("\nLe nom n'est pas dans la liste"); 
			return ST_Liste; 
		} 
		if (strcmp(Laquelle,ST_Liste->refvehicule) == 0) 
		{ 
			ST_Rem = ST_Liste; 
			ST_Liste = ST_Liste->suiv; 
			free(ST_Rem); 
			return ST_Liste; 
		} 
		else 
		{ 
			ST_Liste->suiv = suppRefVe(ST_Liste->suiv,Laquelle); 
			return ST_Liste; 
		} 
} /* fin suppRefVe */

void desalloc(T_CAT *ST_Mail) 
{ 
	if (ST_Mail != NULL) 
	{ 
		desalloc(ST_Mail->suiv); 
		free(ST_Mail); 
	} 
} /* fin desalloc */

void affRefPiece(T_CAT* ST_Liste, int iPiece) 
{ 
	int iTab; 
	T_CAT TEMP; 
	
	printf("\nRéférence Véhicule * N°Pièce * Mise en service* Fin de mise en service 384 *"); 
	printf("\n*************************************************************************************386 **\n"); 
	while(ST_Liste != NULL) 
	{ 
		TEMP = *ST_Liste; 
		for(iTab = 0; (iTab < TMAX-1 ) && (TEMP.refpiece[iTab] != -1); iTab++) 
		{ 
			if(TEMP.refpiece[iTab] == iPiece) 
			{ 
				printf("%21s*", ST_Liste->refvehicule); 
				printf("%18d*", ST_Liste->refpiece[iTab]); 
				printf("%19d*", ST_Liste->dateval[iTab]); 
				if (ST_Liste->dateval[iTab+1] == -1) 
					printf("%25s*", "-----------"); 
				else
					printf("%25d*", ST_Liste->dateval[iTab+1]); 
					printf("\n"); 
			} 
		} 
		ST_Liste = ST_Liste->suiv; 
	} 
	printf("\n*************************************************************************************407 ***\n"); 
} /* fin afficheRefPiece */