/* Copyright(C) Hu Weilong 2017
 */

#include "Logger.h"
#include "MemCplus.h"

#include <thread>

Logger::Logger(const std::string& name){
	_name = name;
	_thread_over = false;
	MemCplus::PutIn(this);
	_double_buffer_queue = (DoubleBufferQueue<Logtask* >*)MemCplus::PutIn(new DoubleBufferQueue<Logtask* >());
}

Logger::~Logger(){
	FlushLogs();
}

/*add appender to appender map*/
void Logger::AddAppender(std::string name, Appender* appender){
	auto it = _appenders.find(name);
	if (it != _appenders.end()){
		return;
	}
	_appenders.insert(std::pair<std::string, Appender* >(name, appender));
}

/*Start a thread for logging*/
void Logger::Start(){
	std::thread log_thread(&Logger::LogThread, this);
	log_thread.detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

/*diffrent log level log message*/
void Logger::Logging(const enum Log_Level log_level, std::string msg){
	Logtask* task = new Logtask(log_level, msg);
	_double_buffer_queue->push(task);	
}

/*shutdown the logger, so free memorry*/
void Logger::Shutdown(){
	_thread_over = true;
	while(_thread_over)
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
	MemCplus::FreeRefs();
}

/*flush logs in task queue*/
void Logger::FlushLogs(){
	FlushLogsInCurQueue();
	_double_buffer_queue->swap();
	FlushLogsInCurQueue();
}

/*flush logs in current comsumer queue*/
void Logger::FlushLogsInCurQueue(){
	while (!_double_buffer_queue->empty()){
		Logtask* task;
		bool is_element = _double_buffer_queue->pop(&task);
		if (is_element){
			for (auto it = _appenders.begin(); it != _appenders.end(); it++){
				if (it->second->CanWriteIn(task->log_level)){
					it->second->AppendLog(task->log_msg);
				}
			}
			delete task;
		}
	}
}

/*log thread*/
void Logger::LogThread(){
	while (!_thread_over){
		if (!_double_buffer_queue->empty()){
			FlushLogsInCurQueue();
		}
		else{
			_double_buffer_queue->swap();
		}
	}
	_thread_over = false;
}
