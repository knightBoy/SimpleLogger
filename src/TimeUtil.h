/* Copyright(C) Hu Weilong 2017
 *
 * time helper for getting time or time string
 */

#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include<string>
#include<time.h>

class TimeUtil{

public:
	/*get current time string*/
	static std::string GetTimeString(){
		//get time str
		char* time_str = (char*)calloc(1, 24 * sizeof(char));
		time_t timep;
		struct tm* p;
		time(&timep);
		//p = gmtime(&timep);
		p = localtime(&timep);
		sprintf(time_str, "%d-%d-%d %d:%d:%d", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday,
			p->tm_hour, p->tm_min, p->tm_sec);
		std::string ss(time_str);
		free(time_str);
		return ss;
	}

	/*get current time*/
	static void GetCurrentTime(time_t& current_time){
		time(&current_time);
	}

	/*get diff second time of two time*/
	static double GetDiffTime(time_t& lhs, time_t& rhs){
		return difftime(rhs, lhs);
	}
};

#endif