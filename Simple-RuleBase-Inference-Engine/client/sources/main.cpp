#include "../headers/common.h"
#include "../headers/Interface.h"

int main(int argc, char *argv[]){
	Interface * ourSRI;

	if(argc == 1){
		ourSRI = new Interface();
		
	}else if(argc == 2){
		// create a command for load of the file passed and execute
		ourSRI = new Interface();
		std::string arg(argv[1]);
		std::string command = "LOAD " + arg;
		ourSRI->commandLine(command);
	}else{
		std::cout << "Usages: ./SRI [path_to_file]\n";
		return 1;
	}
	
	ourSRI -> commandLine();
	return 0;
}