/*	
3.Операции возведения в квадрат и извлечения корня.
*/

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	void *library_handler;
	library_handler = dlopen("/home/popov/Linux/C/lab5/lab5_2/liblab5_2.so",RTLD_LAZY); 
	if (!library_handler){
		fprintf(stderr,"dlopen() error: %s\n", dlerror()); 
		exit(-1); 
	}
	double (*func)(double x); 
	func = dlsym(library_handler, "mypower");  
    int x = 2;
    printf("Квадрат %d = %f\n", x, (*func)(x));
    func = dlsym(library_handler, "mysqrt");  
	x = 4;
    printf("Корень из %d = %f\n", x, (*func)(x));
	dlclose(library_handler); 
    return 0;
}

