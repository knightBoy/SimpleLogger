/* Copyright(C) Weilong Hu 2017
 *
 */

#include "ConfigManager.h"
#include "MemCplus.h"

#include <sstream>
#include <fstream>

ConfigManager::ConfigManager(){
	_config_file_name = "./logger.cfg";
	ReadConfig2Map();
	MemCplus::PutIn(this);
}

/*custom configuration file*/
ConfigManager::ConfigManager(std::string config_file_name) : _config_file_name(config_file_name){
	ReadConfig2Map();
	MemCplus::PutIn(this);
}

ConfigManager::~ConfigManager(){
	//WriteMap2Config();
	_propertities_map.clear();
}

/*get a string propertity*/
std::string ConfigManager::GetStringValue(const std::string& key){
	auto it = _propertities_map.find(key);
	if (it != _propertities_map.end()){
		return it->second;
	}
	return nullptr;
}

/*get a int property*/
int ConfigManager::GetIntValue(const std::string& key){
	auto it = _propertities_map.find(key);
	if (it != _propertities_map.end()){
		std::stringstream ss;
		int result = -1;
		ss << it->second;
		ss >> result;
		return result;
	}
	return -1;
}

/*set a string property*/
void ConfigManager::SetStringValue(const std::string& key, const std::string& newValue){
	_propertities_map[key] = newValue;
}

/*set a int property, convert it to string*/
void ConfigManager::SetIntValue(const std::string& key, const int newValue){
	std::stringstream ss;
	ss << newValue;
	_propertities_map[key] = ss.str();
}

/*get a bool property*/
bool ConfigManager::GetBoolValue(const std::string& key){
	auto it = _propertities_map.find(key);
	if (it != _propertities_map.end()){
		return (it->second == "true" ? true : false);
	}
	return false;
}

/*set a bool property*/
void ConfigManager::SetBoolValue(const std::string& key, const bool newValue){
	_propertities_map[key] = (newValue == true) ? "true" : "false";
}

/*read property file to a map*/
void ConfigManager::ReadConfig2Map(){
	std::ifstream ifs;
	ifs.open(_config_file_name, std::ios::in);
	if (!ifs.is_open()){
		return;
	}
	std::string line;
	while (getline(ifs, line)){
		if (line[0] != '#'){
			int equal_index = line.find_first_of("=");
			std::string key = line.substr(0, equal_index);
			std::string value = line.substr(equal_index + 1);
			_propertities_map[Trim(key)] = Trim(value);
		}
	}
	ifs.close();
}

/*write map to file*/
void ConfigManager::WriteMap2Config(){
	std::ofstream ofs;
	ofs.open(_config_file_name, std::ios::out);
	if (!ofs.is_open()){
		return;
	}

	std::map<std::string, std::string >::iterator it;
	for (it = _propertities_map.begin(); it != _propertities_map.end(); it++){
		std::string line = it->first + "=" + it->second;
		ofs << line << "\n";
	}
	ofs.close();
}

/*remove blank space*/
std::string& ConfigManager::Trim(std::string& str){
	if (str.empty()){
		return str;
	}
	str.erase(0, str.find_first_not_of(" "));
	str.erase(str.find_last_not_of(" ") + 1);
	return str;
}
