#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include "Lock/Mutex.h"

#define FILE_NAME "/home/rtc/Nishant/Logger/Log/Log.txt"

class LoggerThread
{
public:
	LoggerThread(int id);
	~LoggerThread();
	void Start();
	void Run();
	static void* _ThreadProc(void *data);
	//static FILE* fp;
private:
	pthread_t pid;
	int _id;
};


LoggerThread::LoggerThread(int id)
{
	_id = id;
	std::cout << "LoggerThread Instance Created" << std::endl;

}

LoggerThread::~LoggerThread()
{
	pthread_join(pid,NULL);
	std::cout << "LoggerThread Destructor Called" << std::endl;
}


void* LoggerThread::_ThreadProc(void *data)
{
	std::cout << "I Am Here" << std::endl;
	static_cast<LoggerThread*>(data)->Run();
	return NULL;
}

void LoggerThread::Start()
{
	pthread_create(&pid,NULL,&(LoggerThread::_ThreadProc),this);
}

void LoggerThread::Run()
{
	std::cout << "Inside Run Method" << std::endl;
	int i = 0;

	Lock* lock = Lock::GetLock();
	int rslt = lock->TryLock();
	if(rslt == 0)
	{
		FILE* fp = fopen(FILE_NAME,"a");

		for(i = 0;i<5 ;i++)
		{
			fprintf(fp,"%d %s\n",_id,"Writing By Thread Run Method");
		}
		fclose(fp);
		lock->ReleaseLock();
	}
	else
	{
		lock->ReleaseLock();
		std::cout << "SomeOne is Writing" << std::endl;
	}
}
