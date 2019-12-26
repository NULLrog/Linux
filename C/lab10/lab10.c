/*8. Статистический анализ. Имеется несколько массивов данных (разного размера). 
 * Требуется определить математическое ожидание в каждом массиве. 
 * Обработка каждого массива выполняется в отдельном процессе.*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define	MAX 100

struct {
	pthread_mutex_t	mutex;
	int size[MAX];
	int	nput;
} 
shared = { 
	PTHREAD_MUTEX_INITIALIZER
};

void *func(void *arg){
	pthread_mutex_lock(&shared.mutex);
	int *mas = (int *)arg;
	printf("Получен Массив %i, размером %i,\n", shared.nput, shared.size[shared.nput]);
	fflush(stdout);
	int m = 0;
	for (int i = 0; i < shared.size[shared.nput]; i++){
		m += i*mas[i];
	}
	printf("мат.ожидание %i, поток %lu\n", m, pthread_self());
	shared.nput++;
	pthread_mutex_unlock(&shared.mutex);
	return NULL;
}

int **createMas(int count){
	int **mas = malloc(count*sizeof(int *));
	for (int i = 0; i < count; i++){
		int elements = rand() % 10;
		shared.size[i] = elements;
		mas[i] = malloc(elements*sizeof(int));
		printf("Массив %i: ", i);
		for (int j = 0; j < elements; j++){
			mas[i][j] = rand() % 10;
			printf("%d ",mas[i][j]);
		}
		printf("\n");
	}
	return mas;
}

int main(int argc, char *argv[]) {
    pthread_t threads[atoi(argv[1])];
    if (argc < 2) {
        printf("Введите количество массивов!\n");
        exit(-1);
    }
	int **mas = createMas(atoi(argv[1]));
	for (int i = 0; i < atoi(argv[1]); i++) {
		pthread_create(&threads[i], NULL, func, mas[i]);
		sleep(rand()%3);
	}	
	for (int i = 0; i < atoi(argv[1]); i++) {
		pthread_join(threads[i], NULL);
		printf("Поток %lu завершился!\n", threads[i]);	
	}
	for (int i = 0; i < atoi(argv[1]); i++){
        free(mas[i]);
    }
    free(mas);
    return 0;
}
