/* Copyright(C) Hu Weilong 2017
 */

#include "MemCplus.h"

/*put ref into refs set*/
void* MemCplus::PutIn(void* ref){
	_refs.insert((Object*)ref);
	return ref;
}

/*remove the ref from set*/
void MemCplus::Remove(void* ref){
	_refs.erase((Object*)ref);
}

/*free all the refs*/
void MemCplus::FreeRefs(){
	for (auto it = _refs.begin(); it != _refs.end(); it++){
		if (*it != nullptr){
			delete *it;
		}
	}
	_refs.clear();
}

std::set<Object* > MemCplus::_refs;