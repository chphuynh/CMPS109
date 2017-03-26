/* Interface.h */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "common.h"
#include "KnowledgeBase.h"
#include "RuleBase.h"
#include "Inference.h"
#include "TCPServerSocket.h"




using namespace std;

class Interface {
	private: 
		// Helper method for parse
		std::vector<std::string> parseSeg(std::string target);
		// takes a 2d set of string vector and formats it with a header
		char * format(std::vector<std::vector<std::string>> result);
		// helper method for format
		std::string formatSize(int size);
		// ptr to a TCP server Socket
		TCPServerSocket * serverSocket;
	public: 
		// Pointers to kb and rb
		KnowledgeBase * KB;
		RuleBase * RB;
		// interface constructor 
		Interface();
		// takes in a formatted statment and excutes it
		std::vector<std::vector<std::string>> executeCommand(std::vector<std::vector<std::string>> p_command);
		// grab creates a vector of all the rules and facts in the kb and rb
		std::vector<char *> grab();
		// Parse
		char * parse(std::string p_statement);
		~Interface();
		
};
#endif

