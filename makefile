all:client server

client: client.cpp
server: server.cpp

clean:
	rm -f client server 
