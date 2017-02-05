/* Copyright(C) Weilong Hu 2017
 * 
 * read or write the configuration file
 */

#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "Object.h"

#include <string>
#include <map>

class ConfigManager : public Object{

private:
	std::string _config_file_name;
	//all propertities read to this map
	std::map<std::string, std::string > _propertities_map;  

public:
	explicit ConfigManager();
	explicit ConfigManager(std::string config_file_name);
	~ConfigManager();

	//get or set value, but there are only strings in map's value
	std::string GetStringValue(const std::string& key);
	
	int GetIntValue(const std::string& key);

	void SetStringValue(const std::string& key, const std::string& newValue);

	void SetIntValue(const std::string& key, const int newValue);

	bool GetBoolValue(const std::string& key);

	void SetBoolValue(const std::string& key, const bool newValue);

private:
	void ReadConfig2Map();
	void WriteMap2Config();
	std::string& Trim(std::string& str);
};

#endif