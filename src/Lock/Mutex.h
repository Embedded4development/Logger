/*

Author: Nishant Bijani
File_Name: Mutex.h

*/
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

class Lock
{

public:
	static Lock* lockObj;
	~Lock()
	{
		delete Lock::lockObj;
	}

	//Single Ton Design Pattern
	static Lock* GetLock()
	{
		if (!lockObj)
		{
			lockObj = new Lock;
		}
		return lockObj;
	}
	void ReleaseLock();
	void DoLock();
	int TryLock();
private:
	pthread_mutex_t _mutex;

	Lock();

//Class Lock
};

Lock *Lock::lockObj = 0;


Lock::Lock()
{
	pthread_mutex_init(&_mutex,NULL);
}

void Lock::ReleaseLock()
{
	pthread_mutex_unlock(&_mutex);
}

void Lock::DoLock()
{
	pthread_mutex_lock(&_mutex);
}

int Lock::TryLock()
{
	int result = pthread_mutex_trylock(&_mutex);
	if (result == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
