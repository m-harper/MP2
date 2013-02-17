# makefile

all: dataserver client

reqchannel.o: reqchannel.h reqchannel.h
	g++ -c -g reqchannel.c

dataserver: dataserver.c reqchannel.o 
	g++ -pthread -o dataserver dataserver.c reqchannel.o 

simpleclient: simpleclient.c reqchannel.o
	g++ -o simpleclient simpleclient.c reqchannel.o
	
client: client.c reqchannel.o
	g++ -o client client.c reqchannel.o

clean:
	rm dataserver client *.o
