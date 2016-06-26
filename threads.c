#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
int solde;

void* t_pere(void* ptr)
{
	int *ptab;
	ptab=(int*)ptr;

	pthread_mutex_lock(&mutex);
	solde+=*ptab;
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

void* t_fils(void* ptr)
{
	int *ptab;
	ptab=(int*)ptr;

	pthread_mutex_lock(&mutex);
	solde+=*ptab;
	pthread_mutex_unlock(&mutex);


	pthread_exit(NULL);
}

int main(void)
{
	pthread_t thf,thp;
	int ret=0,dep=0,i;
	pthread_mutex_init(&mutex,NULL);

	printf("Combien papa veut mettre d'argent?\n");
	scanf("%d",&dep);

	printf("Combien fiston veut me niquer?\n");
	scanf("%d",&ret);

	for(i=0;i<5;i++)
	{
	pthread_create( &thf, NULL, t_fils, (int*)&ret );
	pthread_create( &thp, NULL, t_pere, (int*)&dep );

	pthread_join(thf,NULL);
	pthread_join(thp,NULL);
	printf("Solde tout compte fait: %d€\n",solde);
	sleep(3);
	}

	return 0;
}
