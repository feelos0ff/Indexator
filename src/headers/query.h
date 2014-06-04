#ifndef QUERY_H
#define QUERY_H

#include "index.h"
#include "ranking.h"


class Query{

    IndexTable *_idx;
    Ranking _rank;

    unsigned long _maxLenQuery;

public:

    PostingList* ExecQuery(string);

};

#endif // QUERY_H
