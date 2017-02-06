    /* Copyright(C) Weilong Hu 2017
 * 
 * there are some constants
 */

#ifndef DEFINE_H
#define DEFINE_H

enum Log_Level{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	FATAL
};

//_MSC_VER
#ifdef _WIN32
#define DLL_LOGGER_API __declspec(dllexport)
#else
#define DLL_LOGGER_API 
#endif

#endif