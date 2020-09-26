// Название: prodcons1.c
// Описание: Пример задачи писателей-читателя с мьютексами 
// и ожиданием доступа потребителем
#include <pthread.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <wait.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define	MAXNITEMS 1000000
#define	MAXNTHREADS 100
#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

static int nitems, potok; /* только для чтения потребителем и производителем */
struct {
	pthread_mutex_t	mutex;
	int	buff[MAXNITEMS];
	int	nput;
	int	nval;
} shared = { 
	PTHREAD_MUTEX_INITIALIZER
};

void *produce(void *), *consume(void *);
int main(int argc, char **argv){
	int i, nthreads, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;
	if (argc != 3) {
		printf("usage: prodcons1 <#items> <#threads>");
		exit(-1);
	}

	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);
	/* создание всех производителей и одного потребителя */
	//Set_concurrency(nthreads + 1);
	//pthread_create(&tid_consume, NULL, consume, NULL);
	for (i = 0; i < nthreads; i++) {
		count[i] = 0;
		pthread_create(&tid_produce[i], NULL, produce, &count[i]);
		potok++;
		//sleep(rand()%1);
	}
	pthread_create(&tid_consume, NULL, consume, NULL);
	/* ожидание завершения производителей и потребителя*/
	for (i = 0; i < nthreads; i++) {
		pthread_join(tid_produce[i], NULL);
		//printf("count[%d] = %d\n", i, count[i]);	
		printf("Producer #%lu makes %d elements\n", tid_produce[i], count[i]);	
	}
	pthread_join(tid_consume, NULL);
	exit(0);
}
void consume_wait(int i){
	for ( ; ; ) {
		pthread_mutex_lock(&shared.mutex);
		//printf("Waiting %d element\n",i);
		if (i < shared.nput) {
		        printf("Element %d ready for consume!\n",i);
			pthread_mutex_unlock(&shared.mutex);
			return;		/* элемент готов */
		}
		printf("Waiting %d element\n",i);
		pthread_mutex_unlock(&shared.mutex);
	}
}
void *produce(void *arg){
	sleep(rand()%10);
	for ( ; ; ) {
		pthread_mutex_lock(&shared.mutex);
		if (shared.nput >= nitems) {
			pthread_mutex_unlock(&shared.mutex);
			return(NULL);/*массив полный,готово*/
		}
		shared.buff[shared.nput] = shared.nval;
		//printf("Producer #%d make element %d with value %d\n",potok,shared.nput,shared.nval);
		printf("Producer #%lu make element %d with value %d\n",pthread_self(),shared.nput,shared.nval);
		shared.nput++;
		shared.nval++;
		pthread_mutex_unlock(&shared.mutex);
		*((int *) arg) += 1;
		sleep(rand()%1);
	}
}
void *consume(void *arg){
	int i;
	for (i = 0; i < nitems; i++) {
		consume_wait(i);
		if (shared.buff[i] != i)
			printf("buff[%d] = %d\n", i, shared.buff[i]);
	}
	return(NULL);
}
