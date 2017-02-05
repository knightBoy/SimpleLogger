/* Copyright(C) Hu Weilong 2017
 */

#include "Appender.h"
#include "MemCplus.h"

#include <fstream>

Appender::Appender(Log_Level prior, std::string log_file){
	_priority = prior;
	_layout = (Layout*)MemCplus::PutIn(new Layout());
	_log_file = log_file;
	MemCplus::PutIn(this);
	Init();
}

Appender::Appender(Log_Level prior, std::string& log_file, Layout* layout){
	_priority = prior;
	_layout = layout;
	_log_file = log_file;
	MemCplus::PutIn(this);
	Init();
}

Appender::~Appender(){
	//write cache
	WriteLogQueue();
}

void Appender::Init(){
	std::string Log_Level_Str[5] = { "[DEBUG]", "[INFO]", "[WARNING]", "[ERROR]", "FATAL" };
	_level_str = Log_Level_Str[_priority];
	_config_manager = new ConfigManager();
}

void Appender::SetConfigManager(ConfigManager* config_manager){
	_config_manager = config_manager;
}

void Appender::SetLayout(Layout* layout){
	_layout = layout;
}

bool Appender::CanWriteIn(enum Log_Level log_priority){
	return log_priority == _priority;
}

void Appender::AppendLog(std::string log_msg){
	if (_config_manager->GetBoolValue("usecache") == true){
		log_msg = _level_str + " " + log_msg;
		log_msg = _layout->FormatLog(log_msg);
		_cache_queue.push(log_msg);
		if (_cache_queue.size() >= 50){
			WriteLogQueue();
		}
	}
	else{
		WriteLog(log_msg);
	}
} 

/*write one log string to file*/
void Appender::WriteLog(std::string log_msg){
	std::ofstream ofs;
	ofs.open(_log_file, std::ios::app);
	if (!ofs.is_open()){
		return;
	}

	//format the log message
	log_msg = _level_str + " " + log_msg;
	log_msg = _layout->FormatLog(log_msg);

	ofs << log_msg << "\n";
	ofs.close();
}

/*write the log queue to file*/
void Appender::WriteLogQueue(){
	std::ofstream ofs;
	ofs.open(_log_file, std::ios::app);
	if (!ofs.is_open()){
		return;
	}
	while (_cache_queue.empty() == false){
		std::string log = _cache_queue.front();
		ofs << log << "\n";
		_cache_queue.pop();
	}
	ofs.close();
}
