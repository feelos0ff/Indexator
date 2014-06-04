#ifndef INDEX_H
#define INDEX_H

#include "parser.h"
#include "ranking.h"
#include "filework.h"
#include "archivate.h"
#include "posting.h"
#include "dbworker.h"
#include "statistics.h"

class Index{

    FileWork _fw;
    DBWorker _db;
    map<string, PostingList > _dictionary;

    int _maxCountOfText;
public:

    void CreateIndex(int stIdx, int endIdx);
    void AddToIndex(int stIdx, int endIdx);

    void Merge(string);
};


class IndexTable{

    map<string, unsigned long long> _tbl;

public:

    void LoadIndex(string);					///< загрузка индекса из файла
    PostingList* FindPos(string);			///< поиск слова

    Statistics* GetStat();					///< выдача статистики
};

#endif // INDEX_H
