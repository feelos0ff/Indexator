#ifndef RANKING_H
#define RANKING_H

#include "definesincludes.h"
#include "posting.h"
#include "index.h"


class Ranking{
	unsigned long _maxRank;
	 DBWorker _db;

public:
	Ranking(unsigned long maxRank = 200):_maxRank(maxRank){}
    PostingList* CuttingList(vector<string>&, IndexTable*);
};

#endif // RANKING_H
