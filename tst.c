#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LI "li_client.bin"
#define BOI 20


//X Partie non faite		//V Partie faite

typedef struct clock //V
{
	int jour;
	int heure;
	int minutes;

}CLOCK;

typedef struct client
{
	//Priorité 1  //V

	int num_client; //numero unique du client
	char boisson[BOI]; //choix de boisson du client
	int nb_verre; //nombre de verre
	int etat; //Client servi(1) ou non-servi(0)
	CLOCK arrive; //heure d'arrivée du client
	struct client *suiv; //pointeur sur client suivant

	//Priorité 2  //X

	int resservir;//Client souhaite une autre boisson(1) ou non(0)


	//Priorité 3 //X

	int solde; //La somme que possède le client et qu'il peut dépenser dans le bar

}CLIENT;


//Priorité 1

int menu(void);
CLOCK hour(void);//Fonction horloge //X

int saisie_date(CLOCK *d); //V

CLIENT * creer_client(int* num); //Creer un client, renseigner tous les champs de la structure sauf depart et le placer dans une liste chaîné //V

int ins_tete(CLIENT **T, CLIENT *N);// Insère le client en tête de liste renvoie -2 -1 ou 1 selon que l'opération ait réussi ou non//V

int suppr_client(CLIENT** T, int num);//Supprime un client lorsque celui-ci quitte le bar //V

int modif_client(CLIENT* T,int num);//Modifie la commande d'un client //V

int sauve_liste(CLIENT *T);//Permets d'enregistrer dans un fichier les informations sur les clients présents dans le bar //V

int recupere_liste(CLIENT **T);//Permets de charger à partir d'un fichier les informations sur les clients présents dans le bar //V

int commande(CLIENT *T);//Fonction qui va classer le client dans un thread approprié selon la boisson qu'il a choisi, décompte le temps de préparation de la boisson et qui renvoie un 1 lorsque le client est servi //X

//Priorité 2

void aff_noeud(CLIENT *N); //AFfiche un client //V

int afficher(CLIENT *N); //Affiche tous les clients présent dans le bar précisant s'il sont servi ou non //V

void resservir(CLIENT *T);//Fonction qui demande au client s'il souhaite être resservi //X

//Priorité 3

int transaction(CLIENT *T,int *solde_bar);//Retire de l'argent du solde du client et le mets dans la caisse du bar //X

int transaction_happy_hour(CLIENT *T, int *solde_bar);//Selon l'heure la bière est moins cher. //X

int tips(CLIENT *T, int *tip);//Donne la possibilité au client de laisser un pourboire // X

void afficher_solde(int *solde_bar);//Pas besoin de faire un dessin //X

int main (void)
{
	CLIENT *C=NULL, *T=NULL;
	int cli=1,p=-5;
	int rep,lq=-1;

	p=recupere_liste(&T);
	if(p>0)
		printf("Les informations ont été récupérées\n");
	else
			printf("Pas d'informations à  récupérer\n");
			sleep(3);

do{
	rep=menu();
	switch(rep)
		{
			case 0 :	p=sauve_liste(T);
					printf("Bye bye, etat de la sauvegarde : %d\n", p);
					break;


			case 1 :	C=creer_client(&cli);
					 p=ins_tete(&T,C);
					printf("Etat de l'insertion: %d",p);
					cli ++;
					break;

			case 2 :	printf("\033c");
					p=afficher(T);
					sleep(5);
					printf("Etat de l'affichage : %d\n", p);
					break;

			case 3 :	printf("Donnez le numero du client qui part du bar\n");
					scanf("%d",&lq);
					p=suppr_client(&T,lq);
					printf("Etat suppression: %d",p);
					break;

			case 4 :
					printf("Quel client souhaite modifier sa commande (numero client) :\n");
					scanf("%d", &lq);
					p=modif_client(T,lq);
					printf("Etat de la modification : %d\n", p);
		}
	}while(rep!=0);

	return 0;
}

int menu(void)
{
	int v=-1;
	printf("\033c");
	printf("\n\n\t\t\tMENU: \n");
	printf("\t --0: Quitter\n");
	printf("\t --1: Creer un client\n");
	printf("\t --2: Afficher tous les clients\n");
	printf("\t --3: Supprimer un client\n");
	/*printf("\t --4: Totaliser le nombre de mouvements depuis le jour J\n");
	printf("\t --5: Calculer la moyenne des mouvements faits\n");
	printf("\t --6: Tracer la courbe des performances\n");
	printf("\t --8: Charger les clients depuis un fichier\n");*/
	printf("\nFaites votre choix: \n");
	scanf(" %d",&v);
	return v;

}

int saisie_date(CLOCK *d)
{
	int status=-1;
	printf("Saisir le jour :\n");
	scanf(" %d", &d->jour);
	printf("Saisir l'heure :\n");
	status*=scanf("%d", &d->heure);
	printf("Saisir la minute :\n");
	status*=scanf("%d", &d->minutes);
	return status;
}


void aff_noeud(CLIENT *N){
		printf("[NUM:%3d  |BOISSON:%s  |NB_VERRE:%d  |ETAT:%d  |ARRIVEE:%2d %2d:%2d]\n",N->num_client,N->boisson,N->nb_verre,N->etat,N->arrive.jour,N->arrive.heure,N->arrive.minutes);
}

int afficher(CLIENT *N){

	if(N==NULL)
	{
		printf("Liste vide...\n");
		return 0;
	}
	else{
		int i=0;
		printf("#NUM:%12s  |BOISSON:%9s  |NB_VERRE:%9s  |ETAT:%13s  |ARRIVEE:%5s %6s:%4s#\n","num client","boisson","nb verre","servi ou non","jour","heure","min");
		while(N!=NULL){
			aff_noeud(N);
			N=N->suiv;
			i++;
		}
		return i;
	}
	return -1;
}

CLIENT* creer_client(int *num)
{
	CLIENT * N=NULL;
	if((N=(CLIENT*)malloc(sizeof(CLIENT)))== NULL)
	{
		printf("Erreur allocation\n");
		return NULL;
	}
	N->num_client = *num;
	printf("Saisir le nom de la boisson\n");
	scanf("%s", N->boisson);
	printf("Saisir le nombre de verre\n");
	scanf("%d", &(N->nb_verre));

	N->etat=0;

	printf("Saisir l'arrivée du client\n");
	saisie_date(&(N->arrive));

	N->suiv=NULL;

	return N;
}

int ins_tete(CLIENT **T, CLIENT *N)
{
	if(N==NULL)
	{
		printf("Insertion annulée\n");
		return -2;
	}
	else
	{
		N->suiv=*T;
		*T=N;
		return 1;
	}

	return -1;
}

int suppr_client(CLIENT **T, int num)
{

	CLIENT *Prec=NULL, *Cour = *T;

	if (Cour == NULL)
	{
		printf("Liste vide\n");
		return 2;
	}

	while(Cour != NULL)
	{
		if (Cour->num_client==num)
		{
			printf("Client trouvée, suppression de l'objet ci-dessous\n");
			aff_noeud(Cour);
			if (Prec == NULL) /* début de liste*/
				*T=(*T)->suiv;
			else
				Prec->suiv=Cour->suiv;
			/* dans tous les cas */
			if (Cour != NULL)
				free(Cour);
			return 1;
		}
		Prec=Cour;
		Cour=Cour->suiv;
	}
	return -1;
}
int modif_client(CLIENT* T,int num){

	int i=0;

	if (T == NULL)
	{
		printf("Liste vide\n");
		return 2;
	}


	while(T != NULL)
	{
		if (T->num_client==num)
		{
			printf("Information trouvée, modification de l'objet ci-dessous\n");
			aff_noeud(T);
			printf("\nVoulez-vous le modifier la boisson ->1, le nombre de verres ->2 rien du tout ->0 ?\n");
			scanf("%d", &i);
			switch(i)
			{
				case 1 :
					printf("Modification de la boisson : \n");
					scanf("%s",T->boisson);
					break;
				case 2 :
					printf("Modification du nombre de verres : \n");
					scanf("%d",&(T->nb_verre));
					break;
				default :
					printf("Aucune modification\n");
			}
			return 1;
		}
		T=T->suiv;
	}

	if(T== NULL)
	{
		printf("Le numéro recherché n'est pas dans la liste\n");
		return 3;
	}
	return -1;
}

/*FILE* ouvrir(FILE *liste_client)
{

	liste_client=fopen(LI,"r+");

	if(liste_client!=NULL)
	{
		printf("\033c");
		printf("\nLe fichier est ouvert avec succès. \n");
		sleep(2);
	}
	else
	{
		printf("\nImpossible d'ouvrir ce fichier car il n'existe pas. \n");
		liste_client=fopen(LI,"w+");
	}

	return liste_client;
}*/

int sauve_liste(CLIENT *T)
{
	FILE * Save=NULL;
	int i=0;

	if((Save=fopen(LI,"wb"))==NULL)
	{
		printf("Erreur d'ouverture du fichier\n");
		return -2;
	}

	while(T != NULL)
	{
		fwrite(T, sizeof(CLIENT),1,Save);
		T=T->suiv;
		i++;
	}

	if(fclose(Save)==0)
		return i;
	else
		return -3;

	return -1;
}


int recupere_liste(CLIENT **T)
{
	FILE * Load=NULL;
	int i=0;
	CLIENT temp, *N=NULL;

		if((Load=fopen(LI,"rb"))==NULL)

	{
		printf("Erreur d'ouverture du fichier\n");
		return -2;
	}
	while(fread(&temp, sizeof(CLIENT),1,Load)==1)
	{
			if((N=(CLIENT*)malloc(sizeof(CLIENT)))== NULL)
			{
				printf("Erreur allocation\n");
				return -5;
			}
			else
				*N=temp;

				i+=ins_tete(T,N);
	}

	if(fclose(Load)==0)
		return i;
	else
		return -3;

	return -1;
}
