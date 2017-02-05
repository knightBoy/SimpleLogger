/* Copyright(C) Hu Weilong 2017
 *
 */

#include "MemCplus.h"

/*put ref into refs set*/
void* MemCplus::PutIn(void* ref){
	_refs.push_back((Object*)ref);
	return ref;
}

/*remove the ref from set*/
void MemCplus::Remove(void* ref){
	for (auto it = _refs.begin(); it != _refs.end(); it++){
		if (*it == ref){
			_refs.erase(it);	
		}
	}
}

/*free all the refs*/
void MemCplus::FreeRefs(){
	for (auto it = _refs.begin(); it != _refs.end(); it++){
		if (*it != nullptr){
			delete *it;
			*it = nullptr;
		}
	}
	_refs.clear();
}

std::vector<Object* > MemCplus::_refs;
