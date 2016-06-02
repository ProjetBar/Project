#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

typedef struct clock
{

	int heure;
	int minutes;
	int jour;

}CLOCK;

void define_date(CLOCK *clk);
void gestion_heure(CLOCK *clk);



int main (void)
{

CLOCK clk;
define_date(&clk);
gestion_heure(&clk);

return 0;
}

void define_date(CLOCK *clk)
{
	printf("Quel heure voulez vous commencé?\n");
	scanf("%d",&clk->heure);
	printf("minutes\n");
	scanf("%d",&clk->minutes);
	printf("Quel jour voulez vous simuler?\n");
	printf("1.Lundi\n");
	printf("2.Mardi\n");
	printf("3.Mercredi\n");
	printf("4.Jeudi\n");
	printf("5.Vendredi\n");
	printf("6.Samedi\n");
	printf("7.Dimanche\n");
	scanf("%d",&clk->jour);
	printf("la simulation commencera à %d:%d Le %d\n",clk->heure, clk->minutes,clk->jour);
}

void gestion_heure(CLOCK *clk)
{
	int t=0;
	time_t debut, fin ;
	debut=time(NULL) ;
	do
	{
	if (t==0)
	{
		clk->minutes=clk->minutes+10;
		t++;
			if(clk->minutes>=60)
			{
			clk->minutes=0;
			clk->heure++;
			}
			if (clk->heure>=24)
			clk->heure=0;
	}
	fin = time(NULL);
	}
	while (difftime(fin, debut)<5);
	printf("%d:%d\n",clk->heure, clk->minutes);
	gestion_heure(clk);
}


