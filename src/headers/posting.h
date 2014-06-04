/*
 * posting.h
 *
 *  Created on: 01 июня 2014 г.
 *      Author: feelosoff
 */

#ifndef POSTING_H_
#define POSTING_H_
#include "definesincludes.h"
#include "filework.h"
#include "archivate.h"


class BasePost{
public:
	virtual ~BasePost(){}

	virtual list<int>* GetEntrance() = 0;
	virtual void Dump(string) = 0;
};


class Post : public BasePost{

	list<int> _entrance;
public:

	void SetEntrance(list<int>&);

	list<int>* GetEntrance();
	void Dump(string);
};


class PostFromDump : public BasePost{
	unsigned long _countEnt;
	unsigned long long _pointEnt;

	FileWork _fw;

public:
	list<int>* GetEntrance();
	void Dump(string);
};


class PostingList{
	///< номер документа, количество вхождений, указатель на смещение, указатель на вхождения
	map<unsigned long ,pair<unsigned long, pair<unsigned long long, BasePost*> > > _posts;

	list<unsigned long> _docId;
	FileWork _fw;
public:

	PostingList();
	~PostingList();

	void Add(unsigned long, list<int>&);					///< добавление документа к текущему постинглисту

	void Merge(unsigned long long);							///< слияние текущего и заданного смещением
	void Merge(PostingList*);								///< слияние текущего и заданного указателем

	unsigned long long Dump(string);						///< запись в файл

	void UpToRAM(unsigned long);							///< загрузка из файла списка фхождений

	unsigned long Length();								///< количество файлов в постинглисте
	unsigned long LengthEnt(unsigned long);					///< количество вхождений в данный файл

	void Load(unsigned long long, string);						///< загрузка постинглиста из файла
	void Load(unsigned long long);							///< загрузка постинглиста изуже открытого файла

	bool IsExist(unsigned long);							///< проверка на вхождение заданного документа

	list<unsigned long>* GetPostingList(){return &_docId;}	///< выдача постинглиста
};


#endif /* POSTING_H_ */
