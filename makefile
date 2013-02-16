# makefile

all: dataserver simpleclient

reqchannel.o: reqchannel.h reqchannel.h
	g++ -c -g reqchannel.c

dataserver: dataserver.c reqchannel.o 
	g++ -pthread -o dataserver dataserver.c reqchannel.o 

simpleclient: simpleclient.c reqchannel.o
	g++ -o simpleclient simpleclient.c reqchannel.o

clean:
	rm dataserver simpleclient *.o
