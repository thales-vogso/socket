#include "SocketServer.h"
#include "SocketException.h"
#include <pthread.h>
#include <iostream>
#include <sstream>
#include <unistd.h>

std::vector<Socket*> SocketServer::_clients;
ThreadReadWriteLock SocketServer::readWriteLock;
bool SocketServer::serviceFlag = true;

SocketServer::SocketServer(const int port)
{
	if ( ! Socket::create() )
	{
		throw SocketException ( "Could not create server socket." );
	}
	
	if ( ! Socket::bind ( port ) )
	{
		throw SocketException ( "Could not bind to port." );
	}
	
	if ( ! Socket::listen() )
	{
		throw SocketException ( "Could not listen to socket." );
	}
}

SocketServer::~SocketServer()
{
	for(std::vector<Socket*>::iterator it = _clients.begin(); it != _clients.end(); it++){
		Socket* client = *it;
		delete client;
		_clients.erase(it);
	}
}

void SocketServer::accept(Socket& socket)
{
	if ( ! Socket::accept ( socket ) )
	{
		throw SocketException ( "Could not accept socket." );
	}
}

bool SocketServer::accept()
{
	Socket* clientSocket = new Socket;
	accept(*clientSocket);
	addClient(clientSocket);
	
	//create new thread for a new client
	pthread_t newThread;
	int res = pthread_create(&newThread, NULL, processMsg, static_cast<void*>(clientSocket));
	if(res!=0)
		return false;
	
	//detach the newThread
	//so when newThread exits it can release it's resource
	res = pthread_detach(newThread);
	if(res!=0){
		//perror("Failed to detach thread");
		std::cout<<"Failed to detach thread"<<std::endl;
	}
	
	return true;
}

void SocketServer::run()
{
	while(serviceFlag)
	{
		if(_clients.size() >= static_cast<unsigned int>(MAXCONNECTION))
			serviceFlag = false;
		else
			serviceFlag = accept();
		sleep(1);
	}
}

void* SocketServer::processMsg(void* arg)
{
	std::string msg;
	Socket* clientSocket = static_cast<Socket*>(arg);
	
	clientSocket->send("Welcome!");
	
	while(serviceFlag)
	{
		clientSocket->receive(msg);
		if(msg.find("exit") == 0){
			clientSocket->send("user_exit");
			delClient(clientSocket);
			break;
		}else{
			std::cout<<"recv msg is "<<msg<<std::endl;
			sendMsg(clientSocket ,msg);
		}
		sleep(1);
	}
	pthread_exit(NULL);
	return NULL;
}


void SocketServer::addClient(Socket* socket)
{
	if(readWriteLock.SetWriteLock()){
		_clients.push_back(socket);
		
		std::cout<<"Now "<<_clients.size()<<" users..";
		std::cout<<"New User: "<<socket->getID()<<" ip :"<<socket->getAddress()<<" "<<socket->getPort()<<std::endl;
		
		readWriteLock.UnLock();
	}else
		serviceFlag=false;
}

void SocketServer::delClient(Socket* socket)
{
	if(readWriteLock.SetWriteLock()){
		for(std::vector<Socket*>::iterator it = _clients.begin(); it != _clients.end(); it++){
			Socket* refer = static_cast<Socket*>(*it);
			if(refer->getID() == socket->getID())
			{
				//delete socket* in list
				delete refer;
				_clients.erase(it);
				std::cout<<"Now "<<_clients.size()<<" users.."<<std::endl;
				break;
			}
		}
		readWriteLock.UnLock();
	}else
		serviceFlag = false;
}
void SocketServer::sendMsg(Socket* socket, const std::string& msg){
	for(std::vector<Socket*>::iterator it = _clients.begin(); it != _clients.end(); it++){
		Socket* refer = static_cast<Socket*>(*it);
		std::stringstream str;
		str<<"user("<<socket->getID()<<") say:"<<msg<<"\n";
		refer->send(str.str());
	}
}
