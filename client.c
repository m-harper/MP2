#include "reqchannel.h"

/*
The client program (to be implemented as program client.C is to fork off a process, which is
supposed to load the data server program (the source code is provided in file dataserver.C. The
client then issues requests to the server through what we will be calling request channels. Request
channels are a simple inter-process communication mechanism, and they are provided by the class
RequestChannel. Request channels provide the following interface:
*/

/*
You are to write a program (call it client.C) that first forks off a process, then loads the provided
data server, and finally sends a series of requests to the data server. Before terminating, the client
sends a quit request and waits for the bye response from the server before terminating. You are
also to write a report that briefly compares the overhead of sending a request to a separate process
compared to handling the request in a local function.
*/

using namespace std;

int main(int argcs, char** argv) {
	// First fork
	
	// Exec dataserver
	
	// Send requests
	
	// Before terminating, send quit request and wait for bye
	
	return 0;
}