#ifndef QUERY_H
#define QUERY_H

#include "index.h"
#include "ranking.h"
#include "pipework.h"

class Query{

    IndexTable *_idx;
    Ranking _rank;

    unsigned long _maxLenQuery;
    PipeWork _pipe;

public:
    Query():_maxLenQuery(10), _idx(NULL){}
    void SetTable(IndexTable *idx){_idx=idx;}
    PostingList* ExecQuery(string);

};

#endif // QUERY_H
