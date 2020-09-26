all: client server udpclient udpserver struct_client struct_server
client:
	gcc TCPEchoClient.c DieWithError.c -o client
	gcc TCPEchoClient2.c DieWithError.c -o client2
server:
	gcc TCPEchoServer.c DieWithError.c HandleTCPClient.c -lpthread -o server
	gcc TCPEchoServer.c DieWithError.c HandleTCPClient2.c -lpthread -o server2
	

udpclient:
	gcc UDPEchoClient.c DieWithError.c -o udpclient
udpserver:
	gcc UDPEchoServer.c DieWithError.c -lpthread -o udpserver
struct_client:
	gcc TCPEchoClientStruct.c DieWithError.c -o struct_client
struct_server:
	gcc TCPEchoServer.c DieWithError.c HandleTCPClientStruct.c -o struct_server
clean:
	rm -f client client2 server server2 client server udpclient udpserver struct_client struct_server
