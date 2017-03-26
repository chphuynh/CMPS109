all:
	make -B client
	make -B server

client: 
	g++ -std=c++11 -pthread client/sources/*.cpp -o clientSRI


server:
	g++ -std=c++11 -pthread server/sources/*.cpp -o serverSRI