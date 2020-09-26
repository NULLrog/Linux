#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#define N 5
struct DATA{
	int a;
	int h;
};
typedef struct DATA Data;
 
void *square_of_triangle(void *arg){
	Data* a = (Data*)arg;
	double *ps = (double*)malloc(sizeof(double)); 
	*ps = 0.5 *a->a * a->h;
	sleep(1);
	printf("square=%f\n", *ps);
	pthread_exit((void*)ps);
	//return (void*)ps;
}

int main(int argc, char * argv[]){
	int result;
	pthread_t threads[N];
	Data data[N];
	void *status[N];
	
	for (int i = 0; i < N; i++){
		data[i].a = i+1;
		data[i].h = (i+1)*N;
		result = pthread_create(&threads[i], NULL, square_of_triangle, &data[i]);
		if (result != 0) {
			perror("Creating the first thread");
			return EXIT_FAILURE;
		}	
	}

	for (int i = 0; i < N; i++){
		result = pthread_join(threads[i], &status[i]);
		if (result != 0) {
			perror("Joining the first thread");
			return EXIT_FAILURE;
		} else {
			printf("square[%d]=%f\n", i,  *((double*)status[i]));
		}
		free(status[i]);
	}

	printf("Done..\n");
	return EXIT_SUCCESS;
}
