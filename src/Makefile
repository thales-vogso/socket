main: ThreadReadWriteLock.o SocketServer.o Socket.o
	g++ -g ThreadReadWriteLock.o SocketServer.o Socket.o main.cpp -I. -lpthread -o server
ThreadReadWriteLock.o: ThreadReadWriteLock.cpp
	g++ -c ThreadReadWriteLock.cpp
SocketServer.o: SocketServer.cpp
	g++ -c SocketServer.cpp
Socket.o: Socket.cpp
	g++ -c Socket.cpp
clean:
	@rm -f server *.o
	@echo 'clean'
