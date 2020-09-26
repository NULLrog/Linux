// Название: prodcons2.c
// Описание: Пример задачи писателей-читателя с мьютексами 
// и условными переменными
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

/* глобальные переменные для всех потоков */
int nitems; /* только для чтения потребителем и производителем */
int buff[MAXNITEMS];

struct {
  pthread_mutex_t mutex;
  int nput;	/* следующий сохраняемый элемент */
  int nval;	/* следующее сохраняемое значение */
} put = { 
	PTHREAD_MUTEX_INITIALIZER 
};

struct {
  pthread_mutex_t	mutex;
  pthread_cond_t	cond;
  int				nready;	/* количество готовых для потребителя */
} nready = { 
PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER
};

void*produce(void *), *consume(void *);

int main(int argc, char **argv){
	int i, nthreads, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;
	if (argc != 3){
		printf("usage: prodcons3 <#items> <#threads>\n");
		exit(-1);
	}
	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

	/* создание всех производителей и одного потребителя */
	for (i = 0; i < nthreads; i++) {
		count[i] = 0;
		pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	pthread_create(&tid_consume, NULL, consume, NULL);

	/* ожидание завершения производителей и потребителя */
	for (i = 0; i < nthreads; i++) {
		pthread_join(tid_produce[i], NULL);
		printf("Producer #%lu makes %d elements\n", tid_produce[i], count[i]);	
	}
	pthread_join(tid_consume, NULL);
	exit(0);
}
void *produce(void *arg){
	sleep(rand()%10);
	for ( ; ; ) {
		pthread_mutex_lock(&put.mutex);
		if (put.nput >= nitems) {
			pthread_mutex_unlock(&put.mutex);
			return(NULL);	/* массив заполнен, готово */
		}
		buff[put.nput] = put.nval;
		put.nput++;
		put.nval++;
		pthread_mutex_unlock(&put.mutex);
		pthread_mutex_lock(&nready.mutex);
		if (nready.nready == 0)
			pthread_cond_signal(&nready.cond);
		nready.nready++;
		pthread_mutex_unlock(&nready.mutex);
		printf("Producer #%lu make element %d with value %d\n",pthread_self(),put.nput,put.nval);
		*((int *) arg) += 1;
	}
}
void *consume(void *arg){
	int i;
	for (i = 0; i < nitems; i++) {
		pthread_mutex_lock(&nready.mutex);
		while (nready.nready == 0){
			printf("Consumer waiting!\n");	
			pthread_cond_wait(&nready.cond, &nready.mutex);
		}
		nready.nready--;
		printf("Use one!\n");
		pthread_mutex_unlock(&nready.mutex);
		if (buff[i] != i)
			printf("buff[%d] = %d\n", i, buff[i]);
	}
	return(NULL);
}
