/*
 * posting.cpp
 *
 *  Created on: 04 июня 2014 г.
 *      Author: feelosoff
 */
#include "../headers/posting.h"


	PostingList();
	~PostingList();

void Add(unsigned long, list<int>&){
	Post *newPost = new Post();

}

	void Merge(unsigned long long);				///< слияние текущего и заданного смещением
	void Merge(PostingList*);					///< слияние текущего и заданного указателем

	unsigned long long Dump(string);			///< запись в файл

	void UpToRAM(unsigned long);				///< загрузка из файла списка фхождений

	unsigned long Length();						///< количество файлов в постинглисте
	unsigned long LengthEnt(unsigned long);		///< количество вхождений в данный файл

	void Load(unsigned long long, string);		///< загрузка постинглиста из файла
	void Load(unsigned long long);				///< загрузка постинглиста изуже открытого файла

bool PostingList::IsExist(unsigned long docId){

	if(_posts.end() ==  _posts.find(docId))
		return false;

	return true;
}



