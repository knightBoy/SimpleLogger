/* Copyright(C) Hu Weilong 2017
 *
 * put in objects which are newd, the class will delete them
 */

#ifndef MEM_PLUS_H
#define MEM_PLUS_H

#include "Object.h"

#include <set>

class MemCplus{

private:
	static std::set<Object* > _refs;

public:
	static void* PutIn(void* ref);
	static void Remove(void* ref);
	static void FreeRefs();
};

#endif