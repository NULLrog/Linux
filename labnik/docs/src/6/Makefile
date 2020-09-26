all : objectFiles
	gcc -o build/file build/file.o
	gcc -o build/spaces build/spaces.o
objectFiles : file.c spaces.c buildDir
	gcc -std=c99 -o build/spaces.o -c spaces.c
	gcc -std=c99 -o build/file.o -c file.c
buildDir :
	mkdir -p build
clean:
	rm -rf  build/file.o build/spaces.o build/file build/spaces
