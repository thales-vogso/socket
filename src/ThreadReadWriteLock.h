/****************************************************************************
*	@Copyright(c)	2015,Vogso
*	@desc	线程锁
*	@date	2015-9-30
*	@author	minamoto
*	@E-mail	jiangtai@wushuang.me
*	@file	ThreadReadWriteLock.h
******************************************************************************/
#ifndef THREADREADWRITELOCK_H
#define THREADREADWRITELOCK_H

#include <pthread.h>

class ThreadReadWriteLock
{
	public:
		ThreadReadWriteLock();
		~ThreadReadWriteLock();
		
		bool SetReadLock();
		bool SetWriteLock();
		void UnLock();
	
	private:
		pthread_rwlock_t readWriteLock;
		static bool _writeable;
};

#endif
