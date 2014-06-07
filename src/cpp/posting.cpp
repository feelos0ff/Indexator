/*
 * posting.cpp
 *
 *  Created on: 04 июня 2014 г.
 *      Author: feelosoff
 */
#include "../headers/posting.h"

PostingList::PostingList(){}

PostingList::~PostingList(){
	map<unsigned long ,pair<unsigned long,
						   pair<unsigned long long, BasePost*> > >::iterator iter = _posts.begin();

	for(;iter !=  _posts.end(); iter++){
		if(iter->second.second.second)
			delete iter->second.second.second;
	}
}

void PostingList::Add(unsigned long docId, list<int>& ent){
	Post *newPost = new Post();
	newPost->SetEntrance(ent);

	_docId.push_back(docId);
	pair<unsigned long, pair<unsigned long long, BasePost*> >  entrance;

	entrance.first = ent.size();
	entrance.second.first = 0;
	entrance.second.second = newPost;

	_posts[docId] = entrance;
}

void PostingList::Merge(unsigned long long pos, string fileName){
	PostingList * newPosting = new PostingList();

	newPosting->Load(pos, fileName);
	Merge(newPosting);

	delete newPosting;
}
void PostingList::Merge(PostingList *secondPost){
	map<unsigned long ,pair<unsigned long,
					   pair<unsigned long long, BasePost*> > >::iterator iter = secondPost->_posts.begin();

	for(; iter != secondPost->_posts.end(); iter++){
		_posts[iter->first] = iter->second;
		_docId.push_back(iter->first);
	}
}

unsigned long long PostingList::Dump(string fileName){
	_fw.OpenWrite(fileName, true);
	unsigned long long pos = _fw.GetPos();

	list<unsigned long long> dataForArchivate;
	map<unsigned long ,pair<unsigned long,
					   pair<unsigned long long, BasePost*> > >::iterator iter = _posts.begin();

	unsigned long long lastDocId = 0;
	unsigned long long lastPointEnt = 0;

	for(int i = 0; iter != _posts.end(); iter++, i = (i + 1) %2){
		unsigned long long data = 0;

		switch(i){
			case 0:
				data = iter->first - lastDocId;
				lastDocId = iter->first;
				break;

			case 1:
				data = iter->second.first;
				break;

		}
		dataForArchivate.push_back(data);
	}

	string results = Archivate::Decode(dataForArchivate);
	_fw.WriteIdxLine(results);
//	pos = _fw.GetPos() - pos;
	_fw.CloseWrite();

	return pos;
}

unsigned long PostingList::Length(){
		return _docId.size();
}
unsigned long PostingList::LengthEnt(unsigned long docId){
	return _posts[docId].first;
}

void PostingList::Load(unsigned long long pos, string fName){
	_fw.OpenRead(fName);
	Load(pos);
	_fw.CloseRead();
}
void PostingList::Load(unsigned long long pos){
	string data = _fw.ReadIdxLine(pos);

	list<unsigned long long> *rawPost = Archivate::Encode(data);
	list<unsigned long long>::iterator iter = rawPost->begin();

	unsigned long docId = 0;
	pair<unsigned long, pair<unsigned long long, BasePost*> >  entrance;

	for(int i = 0; iter != rawPost->end(); iter++, i = (i + 1) %2){
		switch (i){
			case 0:
				docId += *iter;
				break;

			case 1:
				entrance.first = *iter;
				break;
/*
			case 2:
				entrance.second.first += *iter;
				entrance.second.second = NULL;

				_posts[docId] = entrance;
				_docId.push_back(docId);*/
		}
	}

	delete rawPost;
}
bool PostingList::IsExist(unsigned long docId){

	if(_posts.end() ==  _posts.find(docId))
		return false;

	return true;
}



