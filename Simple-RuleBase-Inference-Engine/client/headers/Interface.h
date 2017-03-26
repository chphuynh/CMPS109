/* Interface.h */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "common.h"
#include "../headers/TCPSocket.h"

using namespace std;

class Interface {
	private: 
		// The TCP socket connection for the client
		TCPSocket * mySocket;
		
	public:
		//gets the integers found at the beginning of char*
		int argSize(char * p_arg, int split);
		//converts char * to string
		string convertToStr(char * c_arg);
		//returns 2d vector in format accepted by print_query
		std::vector<std::vector<std::string>> parseSeg(string target, int targetNum, int argNum);
		//method copied from inference 
		void print_query(std::vector<std::vector<std::string>> p_set);
		//formats string so that it can be passed to printquery
		void unformat(char * p_arg);
		// interface constructor 
		Interface();
		// looping command line for user
		void commandLine(std::string p_arg = "");
		// parser for user input
		~Interface();
		
};
#endif

