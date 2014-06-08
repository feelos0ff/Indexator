#ifndef RANKING_H
#define RANKING_H

#include "definesincludes.h"
#include "posting.h"
#include "index.h"
#include "dbworker.h"
#include <algorithm>

class Ranking{
	unsigned long _maxRank;
	DBWorker _db;

public:

	Ranking(unsigned long maxRank = 200):_maxRank(maxRank){}

	PostingList* CuttingList(vector<string>&, IndexTable*);
	PostingList* Bm25Ranking(); // ранжирование bm25
	PostingList* tf_idfRanking();// обычное tf-idf ранжирование
	PostingList* VectorRancking(); //векторное ранжирование
	PostingList* ModelRancking(); // ранжирование с использованием языковых моделей

    double bm25_weight(unsigned long tf, unsigned long df, unsigned long N, int lenD, int avgDl);
    double idf(unsigned long df, unsigned long N);
};

#endif // RANKING_H
