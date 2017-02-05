#ifndef LOGGER_H
#define LOGGER_H

#include "Object.h"
#include "Appender.h"
#include "define.h"
#include "DoubleBufferQueue.h"

#include <map>
#include <atomic>
#include <mutex>
#include <condition_variable>

/*tasks which are put into the double buffer queue*/
typedef struct Logtask{
	Logtask(Log_Level level, std::string msg) : log_level(level), log_msg(msg)
	{
	}
	Log_Level log_level;
	std::string log_msg;
}Logtask;

class Logger : public Object{

private:
	std::string _name;
	std::map<std::string, Appender* > _appenders;
	DoubleBufferQueue<Logtask* >* _double_buffer_queue;

	std::atomic<bool> _thread_over;
	std::mutex _mtx;
	std::condition_variable _cv;

public:
	explicit Logger(const std::string& name);

	~Logger();

	void AddAppender(std::string name, Appender* appender);

	void Start();

	/*the function to log diffrent level logs*/
	void Logging(const Log_Level log_level, std::string msg);

	/*clear memorry*/
	void Shutdown();

private:
	void FlushLogs();
	void FlushLogsInCurQueue();

protected:
	void LogThread();
};

#endif
