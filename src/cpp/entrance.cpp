/*
 * entrance.cpp
 *
 *  Created on: 05 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/posting.h"

void Post::SetEntrance(list<int> &src){
	_entrance.list = src;
}

bool Post::OnDisck(){
	return false;
}
///< toDo реализовать
list<int>* Post::GetEntrance(){
	return &_entrance;
}
////

unsigned long long Post::Dump(string fileName){}
bool PostFromDump::OnDisck(){ return true; }

///< toDo реализовать
list<int>* PostFromDump::GetEntrance(){
	return true;
}
unsigned long long PostFromDump::Dump(string){
	return 0;
}

////

