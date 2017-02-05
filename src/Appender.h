/* Copyright(C) Hu Weilong 2017
 * 
 * use this class to add log message to file
 */

#ifndef APPENDER_H
#define APPENDER_H

#include "Object.h"
#include "Layout.h"
#include "define.h"
#include "ConfigManager.h"

#include <queue>

class Appender : public Object{

private:
	std::string name;
	Layout* _layout;
	//if log's priority superior than _priority, it can be writen to the file
	Log_Level _priority;
	std::string _log_file;
	std::string _level_str;

	//configManager
	ConfigManager* _config_manager;

	//cache queue
	std::queue<std::string > _cache_queue;

public:
	explicit Appender(Log_Level prior, std::string log_file);
	explicit Appender(Log_Level prior, std::string& log_file, Layout* layout);

	~Appender();

private:
	void Init();
	void WriteLog(std::string log_msg);
	void WriteLogQueue();
public:
	void SetConfigManager(ConfigManager* config_manager);
	void SetLayout(Layout* layout);
	bool CanWriteIn(enum Log_Level log_priority);

	//write log to file
	virtual void AppendLog(std::string log_msg);
};

#endif
