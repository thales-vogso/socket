#include "Socket.h"
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int Socket::increaseID = 100001;

Socket::Socket()
:_sockfd(-1)
{
	_id = increaseID++;
}

Socket::~Socket()
{
	if(isValid())
		::close(_sockfd);
}

//server function
bool Socket::create()
{
	_sockfd = socket(AF_INET,SOCK_STREAM, 0);
	return isValid();
}

bool Socket::bind(const char* host, const int port)
{
	if(!isValid())
		return false;
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = host?inet_addr(host):htonl(INADDR_ANY);//域名
	_address.sin_port = port?htons(port):htons(DEFAULT_PORT);//端口
	
	int res = ::bind(_sockfd, (struct sockaddr*)&_address, sizeof(_address));
	return res != -1;
}
bool Socket::bind(const int port){
	return bind(NULL, port);
}
bool Socket::bind(){
	return bind(NULL, NULL);
}

bool Socket::listen()const
{
	if(!isValid())
		return false;
	int res = ::listen(_sockfd, MAXCONNECTION);
	return res != -1;
}

bool Socket::accept(Socket& clientSocket) const
{
	int clientaddrLength = sizeof(clientSocket._address);
	clientSocket._sockfd = ::accept(_sockfd, (struct sockaddr*)&clientSocket._address, (socklen_t *)&clientaddrLength);
	
	return clientSocket.isValid();
}
//end server functions

bool Socket::connect(const std::string& host,const int port)
{
	if(!isValid())
		return false;
	
	_address.sin_family = AF_INET;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = inet_addr(host.c_str());
	
	int res = ::connect(_sockfd, (struct sockaddr*)&_address, sizeof(_address));
	return res != -1;
}

// Data Transmission
bool Socket::send(Socket& socket,const std::string& msg) const
{
	int res = ::send(socket._sockfd, msg.c_str(), msg.length(), MSG_NOSIGNAL);
	return res != -1;
}
bool Socket::send(const std::string& msg) const
{
	int res = ::send(_sockfd, msg.c_str(), msg.length(), MSG_NOSIGNAL);
	return res != -1;
}

int Socket::receive(Socket& socket,std::string& msg) const
{
	char buffer[MAXRECEIVE+1];
	msg.clear();
	memset(buffer, 0, MAXRECEIVE+1);
	
	int res = ::recv(socket._sockfd, buffer, MAXRECEIVE, 0);
	if(res==-1){
		std::cout<<"error in Socket::Receive\n"<<std::endl;
		return 0;
	}else if(res==0){
		return 0;
	}else {
		msg = buffer;
		return res;
	}
}
int Socket::receive(std::string& msg) const
{
	char buffer[MAXRECEIVE+1];
	msg.clear();
	memset(buffer, 0, MAXRECEIVE+1);
	
	int res = ::recv(_sockfd, buffer, MAXRECEIVE, 0);
	if(res==-1){
		std::cout<<"error in Socket::Receive\n"<<std::endl;
		return 0;
	}else if(res==0){
		return 0;
	}else {
		msg = buffer;
		return res;
	}
}

int Socket::getAddress(){
	return _address.sin_addr.s_addr;
}
int Socket::getPort(){
	//return 8843;
	return _address.sin_port;
}
int Socket::getID(){
	return _id;
}

void Socket::setNonBlocking(const bool flag)
{
	if(isValid())
	{
		int opts;
	
		opts = fcntl ( _sockfd,
	             F_GETFL );
	
		if ( opts < 0 ){
			return;
		}
	
		if ( flag )
			opts = ( opts | O_NONBLOCK );
		else
			opts = ( opts & ~O_NONBLOCK );
	
		fcntl ( _sockfd,
			F_SETFL,opts );
	}
}

bool Socket::isValid() const
{
    //if call function socket fail,it returns -1
	return _sockfd!=-1;
}
