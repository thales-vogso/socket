/****************************************************************************
*	@Copyright(c)	2015,Vogso
*	@desc	异常
*	@date	2015-9-30
*	@author	minamoto
*	@E-mail	jiangtai@wushuang.me
*	@file	SocketException.h
******************************************************************************/
#ifndef SocketException_H
#define SocketException_H

#include <string>

class SocketException
{
	public:
		SocketException ( std::string description ) : _description( description ) {};
		~SocketException (){};
		std::string Description() { return _description; }
	private:
		std::string _description;
};

#endif