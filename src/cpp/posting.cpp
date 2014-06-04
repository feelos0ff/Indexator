/*
 * posting.cpp
 *
 *  Created on: 04 июня 2014 г.
 *      Author: feelosoff
 */
#include "../headers/posting.h"


PostingList::PostingList(){}
PostingList::~PostingList(){}

void Add(unsigned long, list<int>&){
	Post *newPost = new Post();

}

void PostingList::Merge(unsigned long long);				///< слияние текущего и заданного смещением
void PostingList::Merge(PostingList*);					///< слияние текущего и заданного указателем

unsigned long long PostingList::Dump(string){

}
/// ?????
void PostingList::UpToRAM(unsigned long){}				///< загрузка из файла списка фхождений
///
unsigned long PostingList::Length(){
		return _docId.size();
}
unsigned long PostingList::LengthEnt(unsigned long docId){
	return _posts[docId].first;
}

void PostingList::Load(unsigned long long pos, string fName){
	_fw.CloseRead();
	_fw.OpenRead(fName);
	Load(pos);
}
void PostingList::Load(unsigned long long pos){
	string data = _fw.ReadIdxLine(pos);

	list<unsigned long long> *rawPost = Archivate::Encode(data);
	list<unsigned long long>::iterator iter = rawPost->begin();

	unsigned long docId = 0;
	pair<unsigned long, pair<unsigned long long, BasePost*> >  entrance;

	for(int i = 0; iter != rawPost->end(); iter++, i = (i + 1) %3){
		switch (i){
			case 0:
				docId += *iter;
				break;

			case 1:
				entrance.first = *iter;
				break;

			case 2:
				entrance.second.first += *iter;
				entrance.second.second = NULL;

				_posts[docId] = entrance;
				_docId.push_back(docId);
		}
	}

	delete rawPost;
}
bool PostingList::IsExist(unsigned long docId){

	if(_posts.end() ==  _posts.find(docId))
		return false;

	return true;
}



