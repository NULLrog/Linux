run: all
	./amessage_serialize 10 2 | ./amessage_deserialize 
all:
	protoc-c --c_out=. amessage.proto
	gcc -std=c99 amessage.pb-c.c amessage_serialize.c -o amessage_serialize -lprotobuf-c
	gcc -std=c99 amessage.pb-c.c amessage_deserialize.c -o amessage_deserialize -lprotobuf-c

clean:
	rm -f amessage_serialize amessage_deserialize
