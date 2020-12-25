#include "ThreadReadWriteLock.h"

bool ThreadReadWriteLock::_writeable = true;
ThreadReadWriteLock::ThreadReadWriteLock(){

}
ThreadReadWriteLock::~ThreadReadWriteLock(){

}
bool ThreadReadWriteLock::SetReadLock(){
	return true;
}
bool ThreadReadWriteLock::SetWriteLock(){
	if(_writeable){
		_writeable = false;
		return true;
	}else{
		return false;
	}
}
void ThreadReadWriteLock::UnLock(){
	_writeable = true;
}
