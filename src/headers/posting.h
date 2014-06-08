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
#include "statistics.h"

class PostingList {
    ///< номер документа, количество вхождений
    map<unsigned long , unsigned long > _posts;

    list<unsigned long> _docId;
    FileWork _fw;
    Statistics *_st;
public:

    PostingList ( Statistics *st = NULL );
    ~PostingList();

    void Add ( unsigned long, unsigned long );					///< добавление документа к текущему постинглисту

    void Merge ( unsigned long long, string );							///< слияние текущего и заданного смещением
    void Merge ( PostingList* );								///< слияние текущего и заданного указателем

    unsigned long long Dump ( string );						///< запись в файл


    unsigned long Length();								///< количество файлов в постинглисте
    unsigned long LengthEnt ( unsigned long );					///< количество вхождений в данный файл

    void Load ( unsigned long long, string );						///< загрузка постинглиста из файла
    void Load ( unsigned long long );							///< загрузка постинглиста изуже открытого файла

    bool IsExist ( unsigned long );							///< проверка на вхождение заданного документа

    list<unsigned long>* GetPostingList() {
        return &_docId;   ///< выдача постинглиста
    }
};


#endif /* POSTING_H_ */
