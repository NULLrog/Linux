#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#define N 5

void *func(void *arg){
	for (int i = 0; i<5; i++){
		sleep(1);
		printf("pthread id=%d iteration i=%d\n", pthread_self(), i);
	}
	return NULL;
}

int main(int argc, char * argv[]){
	int result;
	pthread_t threads[N];
	
	for (int i = 0; i < N; i++){
		result = pthread_create(&threads[i], NULL, func, NULL);
		if (result != 0) {
			perror("Creating the first thread");
			return EXIT_FAILURE;
		} else {
			pthread_detach(threads[i]);
		}
			
	}
	sleep(N*2);
	printf("Done..\n");
	return EXIT_SUCCESS;
}
