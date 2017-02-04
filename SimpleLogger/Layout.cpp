/* Copyright(C) Hu Weilong 2017
 * implements layout.h
 */

#include "Layout.h"
#include "MemCplus.h"
#include "TimeUtil.h"

Layout::Layout(){
	MemCplus::PutIn(this);
}

/*this function will be called by appender*/
std::string Layout::FormatLog(std::string& raw_msg){
	std::string msg = TimeUtil::GetTimeString();
	return msg + "  " + raw_msg;
}