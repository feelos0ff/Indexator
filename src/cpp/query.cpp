#include "../headers/query.h"


PostingList* Query::ExecQuery ( string query ) {
    vector<string> words = Parser::NormalizeText ( query );

    PostingList *p = _rank.CuttingList ( words, _idx );
    _pipe.WriteQuery ( p, words );

    return p;
}
