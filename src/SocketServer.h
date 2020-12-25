/****************************************************************************
*	@Copyright(c)	2015,Vogso
*	@desc	服务
*	@date	2015-9-30
*	@author	minamoto
*	@E-mail	jiangtai@wushuang.me
*	@file	SocketServer.h
******************************************************************************/
#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <vector>
#include <semaphore.h>
#include "Socket.h"
#include "ThreadReadWriteLock.h"

class SocketServer:public Socket
{
	public:
		/**
		 *	构造函数
		 *	@param	port	端口
		 */
		SocketServer(const int port);
		SocketServer();
		/**
		 *	析构函数
		 */
		virtual ~SocketServer();
		/**
		 *	接收
		 */
		void accept(Socket& socket);
		//run server to connect multi-clients
		/**
		 *	运行
		 */
		void run();
	
	private:
		//accept multi-clients
		/**
		 *	接收
		 */
		bool accept();
		/**
		 *	添加客户端
		 *	@param	clientSocket	客户端
		 */
		void addClient(Socket* clientSocket);
		/**
		 *	删除客户端
		 *	@param	clientSocket	客户端
		 */
		static void delClient(Socket* clientSocket);
		/**
		 *	多线程接收多客户端信息
		 */
		static void* processMsg(void* arg);
		/**
		 *	发送消息
		 *	@param	msg	消息
		 *	@param	fri	好友
		 */
		static void sendMsg(Socket* socket, const std::string& msg);
		static void sendMsg(const std::string& message, std::vector<int> fri);
		/**
		 *	客户端列表
		 */
		static std::vector<Socket*> _clients;
		/**
		 *	服务器状态
		 */
		static bool serviceFlag;
		/**
		 *	读写锁定，用于同步线程
		 */
		static ThreadReadWriteLock readWriteLock;
};

#endif
