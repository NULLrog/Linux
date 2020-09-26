run:
	gcc test.c -o test -fno-strict-overflow -fno-stack-protector -z execstack -mpreferred-stack-boundary=4 -ggdb
	./test < test.dat