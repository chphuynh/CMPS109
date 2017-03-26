#include "../headers/Interface.h"

// default constructor
// Asks users for address and port of 
// server and creates a new object using those
// values
Interface::Interface(){
	// recieve address and port from user
	std::string p_address;
	while(p_address.empty()){
		std::cout << "Please enter my address:";
		getline(std::cin, p_address);
	}
	const char * p_address_char = p_address.c_str();

	std::string p_port;
	while(p_port.empty()){
		std::cout << "Please enter the port of the server:";
		getline(std::cin, p_port);
	}
	int port = std::stoi(p_port);
	
	// the socket for the client
	mySocket = new TCPSocket(p_address_char, port);

	// kills program if connection refused
	if(mySocket->isPeerDisconnected()){
		exit(1);
	}

}


// print_query takes a set of results and prints them nicely to stdout
void Interface::print_query(std::vector<std::vector<std::string>> p_set){
	for(int i = 1; i < p_set[0].size(); ++i){
		for (int j = 0; j < p_set.size(); ++j){
			if(j == p_set.size()-1){
			std::cout << p_set[j][0] << ":" << p_set[j][i];
			}else{
			std::cout << p_set[j][0] << ":" << p_set[j][i] << ", ";
			}
		}
		std::cout << '\n';
	}
}

int Interface::argSize(char * p_arg, int split){
	// i is used to iterate through for loops
	int i;
	//a is temporarily used to hold new int
	int a;
	//targets holds int to be returned
	int targets;
	//split == 0 is used for first num
	if (split == 0){
		for(i = 0; i < 4; i++){
			//turns into int
			a = p_arg[i] - '0';
			//first digit would be a one digit number
			if (i==0){
				targets = a;
			}
			//multiply current digits by 10 to move place value
			else {
				targets = (targets * 10) + a;
			}
		}
		return targets;
	}
	//split == 1 is used for the second digit
	else{
		//start at index 4 now
		for(i = 4; i < 8; i++){
			//turns char into int
			a = p_arg[i] - '0';
			//first digit would be a one digit number
			if (i == 4) {
				targets = a;
			}
			//multiply current digits by 10 to move place value
			else {
				targets = (targets * 10) + a;
			}
			
		}
		//return integer
		return targets;
	}
}

std::vector<std::vector<std::string>> Interface::parseSeg(string target, int targetNum, int argNum) {
        //hodls vector to be returned
        std::vector<std::vector<std::string>> result;
        //iterates through for loop
        int c;
        for (c = 0; c < targetNum; c++){
        	//new segement made each loop
            std::vector<std::string> segment;
            //gets substring before |
            auto rName = target.substr(0, target.find('|'));
            //count keeps track of how many elements have been iterated in the while loop
            int count = 0;
            segment.push_back(rName);
            target.erase(0, target.find('|') + 1);
            auto rParams = target.substr(0, target.find('$'));
            size_t pos = 0;
            std::string token;
            //while loop parses all paramenters
            while ((pos = rParams.find('|')) != std::string::npos) {
                    token = rParams.substr(0,pos);
                    segment.push_back(token);
                    rParams.erase(0, pos + 1);
                    count++;
                    //once all parameters have been parsed, push back whole vector
                    if (count == argNum){
                        result.push_back(segment);
                    }
            }
        
            target.erase(0, target.find('$'));
            if(!rParams.empty()) segment.push_back(rParams);
        }
        return result;
}

string Interface::convertToStr(char * c_arg) {
	string result;
	//starts at index 8 because every index before that is irrelevant
	int i = 8;
	while(c_arg[i]!=NULL) {
		//adds char to string
		result += c_arg[i];
		i++;
	}
	return result;
}

void Interface::unformat(char * p_arg){
	//get num of targets and elements
	int targets = argSize(p_arg,0);
	int elements = argSize(p_arg,1);
	//convert char * to string starting after numbers
	string arg = convertToStr(p_arg);
	std::vector<std::vector<std::string>> unformated = parseSeg(arg,targets,elements);
	print_query(unformated);
	
}

// commandLine is a client method for interface.  It deals with
// all commands, written and read from the socket
void Interface::commandLine(std::string p_arg){
	// infintley loopsing
	std::string statement = p_arg;
	// p_arg = ""
	while(1){
		// nice thing for users
		

		// get the command entered by the user
		if(statement.empty()){
			std::cout << "SRI Session:";
			std::getline(std::cin, statement);
		}
		// if it wasnt a return char
		if(statement.length() > 0){
			// If the command is load we iterate through each line in the 
			// file and pass it to the server
			if(statement.substr(0,4) == "LOAD"){
				// get the pathname of the file
				std::string pathName = statement.substr(5,std::string::npos);

				// Grabs the path type of the file
				std::string pathCheck = pathName.substr(pathName.rfind("."));
				
				// Errors if incorrect path type
				if(pathCheck != ".sri") {
					std::cout << "Invalid file. Please use a .sri file.\n";
					return;
				}

				std::ifstream file(pathName);
				// if we successfully opened the file
				if (file.is_open()){
					std::string line;
					// while there are lines to get
					while(std::getline(file, line)){
						// Send each line to be parsed by server
						const char * p_line = line.c_str();
						mySocket->writeToSocket(p_line, 1000);

						// create a buffer to wait for a return from the server
						char * temp_buffer;
						temp_buffer = (char*)calloc(1000, sizeof(char));
						// read from socket
						if(mySocket->readFromSocket(temp_buffer, 1000) == -1){
							std::cout << "Reading from clientSocket Failed\n";
							mySocket->setPeerDisconnected(true);
							return;
						}
						// if response was "null", it was a success
						// we need this so we dont saturate the server with commands
						// we block until a response
 						if(strcmp((const char *)temp_buffer,"null") != 0){
 							// breaks if its not null
							break;
						}
					}
				} else {std::cout << "Error opening file" << std::endl;}
			// if were a dump, tell the server, and take each returned buffer and input
			// into a file
			} else if(statement.substr(0,4) == "DUMP") {
				// inform the server we request a dump
				const char * p_statement = statement.c_str();
				mySocket->writeToSocket(p_statement, 1000);

				// retrieve pathname
				std::string pathName = statement.substr(5,std::string::npos);

				// Grabs the path type of the file
				std::string pathCheck = pathName.substr(pathName.rfind("."));
				
				// Errors if incorrect path type
				if(pathCheck != ".sri") {
					std::cout << "Invalid file. Please use a .sri file.\n";
					return;
				}				
				std::ofstream outFile(pathName);

				// on success of file open
				if(outFile.is_open()){
					// we break from this loop when the server sends a '\0'
					while(true) {
						// read from the socket into buffer
						char * temp_buffer;
						temp_buffer = (char*)calloc(1000, sizeof(char));

						if(mySocket->readFromSocket(temp_buffer, 1000) == -1){
							std::cout << "Reading from clientSocket Failed\n";
							mySocket->setPeerDisconnected(true);
							return;
						}
						// if its not the null terminator
						if(strcmp((const char *)temp_buffer,"\0") == 0){
							break;
						}
						// convert to string and input it into file
						std::string bufferString;
						int i = 0; 
						while(temp_buffer[i] != '\0') {
							bufferString += temp_buffer[i];
							i++;
						}

						outFile << bufferString << std::endl;

						// send a null character on success of entering
						char * buffer =(char *) calloc(4, sizeof(char));
						buffer[0] = 'n'; buffer[1] = 'u'; buffer[2] = 'l'; buffer[3] = 'l';
						mySocket->writeToSocket(buffer, 1000);
						// Send response here asking for more
					}
					// Buffer finished
					outFile.close();
				} else {std::cout << "Error opening file" << std::endl;}
			// every other command send as plain buffer to server
			} else {
				const char * p_statement = statement.c_str();
				mySocket->writeToSocket(p_statement, 1000);
				if (statement == "x") {
					delete(mySocket);
					exit(1);
					// break;
				}

				char * temp_buffer;
				temp_buffer = (char*)calloc(1000, sizeof(char));

				if(mySocket->readFromSocket(temp_buffer, 1000) == -1){
					std::cout << "Reading from clientSocket Failed\n";
					mySocket->setPeerDisconnected(true);
					return;
				}
				// we have a char * with a header returned. if its not null,
				// (i.e. a response on something that need to be printed)
				// expand the header and wirte to stodut
				if(strcmp((const char *)temp_buffer,"null") != 0){
					unformat(temp_buffer);
				}
			}
		}
		statement = "";	
	}
}

Interface::~Interface(){
	delete(mySocket);
}

