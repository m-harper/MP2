#include "reqchannel.h"
#include "sstream"
#include <cstdlib>
#include <unistd.h>

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

// Returns if the program should fork or run locally
bool handle_args(int, char**);

// Function for running locally
string process_request(string);

string int2string(int);

int main(int argcs, char** argv) {
	bool run_mode = handle_args(argcs, argv);
	
	if (run_mode) {
		// Run forked
		int pid = 0;
		
		pid = fork();
		
		switch (pid) {
		case -1:
			cerr << "Failed to fork\n";
			exit(-1);
			break;
		case 0:
			// This is a child process
			// Start the data server
			execv("dataserver", NULL);			
			break;
		default:
			// This is the parent process
			// Set up request channel
			RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
			
			// Send some requests
			string reply1 = chan.send_request("hello");
			cout << "Reply to request 'hello' is '" << reply1 << endl;

			string reply2 = chan.send_request("data Joe Smith");
			cout << "Reply to request 'data Joe Smith' is '" << reply2 << endl;
			
			string reply3 = chan.send_request("quit");
			cout << "Reply to request 'quit' is '" << reply3 << endl;
			usleep(1000000);
			break;
		}
	}
	else {
		// Run locally
		string rep1, rep2, rep3;
		
		// Send a number of requests
		rep1 = process_request("hello");
		cout << "Reply to request 'hello' is " << rep1 << endl;
		
		rep2 = process_request("data Joe Smith");
		cout << "Reply to request 'data Joe Smith' is " << rep2 << endl;
		
		rep3 = process_request("quit");
		cout << "Reply to request 'quit' is " << rep3 << endl;
				
		if (rep3 == "bye") {
			exit(0);
		}
	}
		
	return 0;
}

/*
 *  Returns if the program should fork or run locally
 *  True means fork, false, run locally
 *  If no arguments given (or incorrect arguements), return true to fork
 */
bool handle_args(int argc, char** argv) {
	// No arguement given, return true
	if (argc == 1) {
		return true;
	}	
	else if (argc == 2) {
		// Correct number of arguements given
		char arg = *(argv[1]);
		if (arg == '1')
			return false;
		if (arg == '2')
			return true;
		// Arguement was incorrect, return true by default
		cerr << "Unknown arguement " << arg << ", defaulting to fork" << endl;
		return true;
	}
	else {
		cerr << "Incorrect number of arguements, defaulting to fork" << endl;
		return true;
	}
}

string process_request(string _request) {
	if (_request == "hello") {
		return "hello to you too";
	}
	else if (_request.substr(0,4) == "data") {
		return int2string(rand() % 100);
	}
	else if (_request == "quit") {
		return "bye";
	}
	else {
		return "unknown request";
	}
}

string int2string(int number) {
   stringstream ss;
   ss << number;
   return ss.str();
}
