/*
 * ranking.cpp
 *
 *  Created on: 02 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/ranking.h"

PostingList* Ranking::CuttingList(vector<string> &query, IndexTable *idx){
	int len = query.size();
	map<unsigned int, unsigned int> rank;
/*	for(int i = 0; i < len; ++i){
		PostingList *tmp = idx->FindPos(query[i]);
		double idf = _db.GetCountTxt() / (double)tmp->Length();

	}*/
}
