/****************************************************************************
*	@Copyright(c)	2015,Vogso
*	@desc	自定义socket类
*	@date	2015-9-30
*	@author	minamoto
*	@E-mail	jiangtai@wushuang.me
*	@file	Socket.h
******************************************************************************/
#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

class Socket
{
	public:
		/**
		 *	构造函数
		 */
		Socket();
		/**
		 *	析构函数
		 */
		virtual ~Socket();
		/**
		 *	服务端初始化
		 */
		bool create(); //create a socket
		/**
		 *	绑定
		 *	@param	host	地址
		 *	@param	port	端口
		 */
		bool bind(const char* host, const int port);
		bool bind(const int port);
		bool bind();
		/**
		 *	侦听
		 */
		bool listen() const;
		/**
		 *	接收
		 */
		bool accept(Socket& clientSocket) const;
		/**
		 *	客户端初始化
		 *	@param	host	地址
		 *	@param	port	端口
		 */
		bool connect(const std::string& host,const int port);
		/**
		 *	发送消息
		 *	@param	socket	客户端
		 *	@param	msg	消息
		 *	@return	结果
		 */
		bool send(Socket& socket,const std::string& msg) const;
		bool send(const std::string& msg) const;
		/**
		 *	接收消息
		 *	@param	socket	客户端
		 *	@param	msg	消息
		 *	@return	结果
		 */
		int receive(Socket& socket,std::string& msg) const;
		int receive(std::string& msg) const;
		/**
		 *	获取地址
		 */
		int getAddress();
		/**
		 *	获取端口
		 */
		int getPort();
		/**
		 *	获取唯一标识
		 */
		int getID();
		/**
		 *	阻挡
		 */
		void setNonBlocking(const bool flag);
		/**
		 *	是否有效
		 */
		bool isValid() const;
		/**
		 *	链接总数
		 */
		static const int MAXCONNECTION = 5;
		/**
		 *	接收信息总数
		 */
		static const int MAXRECEIVE = 255;
		/**
		 *	默认端口
		 */
		static const int DEFAULT_PORT = 8843;
	private:
		/**
		 *	接口
		 */
		int _sockfd;
		/**
		 *	地址
		 */
		struct sockaddr_in _address;
		/**
		 *	唯一标示
		 */
		int _id;
		/**
		 *	分配id
		 */
		static int increaseID;
};

#endif
