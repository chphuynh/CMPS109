#include "../headers/common.h"
#include "../headers/Interface.h"
#include "../headers/GarbageCollector.h"
#include "../headers/TCPServerSocket.h"
#include "../headers/Connection.h"



int main(int argc, char *argv[]){
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


	if(argc == 1){

		TCPServerSocket * tcpServerSocket = new TCPServerSocket(p_address_char, port, 100);
		GarbageCollector * garbageCollector = new GarbageCollector();

		tcpServerSocket->initializeSocket();
		for(;;){
			TCPSocket * tcpSocket = tcpServerSocket->getConnection();
			if(tcpSocket == NULL){
				break;
			}
			garbageCollector->cleanup();
			Interface * inter = new Interface();
			Connection * c = new Connection(tcpSocket, inter);
			c->start();
			garbageCollector->addConnection(c);
		}
		delete(garbageCollector);
		delete(tcpServerSocket);
	}else{
		std::cout << "Usages: ./SRI [path_to_file]\n";
		return 1;
	}
	
	return 0;
}