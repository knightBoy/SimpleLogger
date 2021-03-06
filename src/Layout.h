/* Copyright(C) Hu Weilong 2017
 * it's task is to control the format of the log message
 */

#ifndef LAYOUT_H
#define LAYOUT_H

#include "Object.h"
#include "define.h"

#include <string>

class DLL_LOGGER_API Layout : public Object{

public:
	explicit Layout();
	~Layout(){}

	virtual std::string FormatLog(std::string& raw_msg);
};

#endif