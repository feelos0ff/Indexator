#include "../headers/query.h"


PostingList* Query::ExecQuery(string query){
    vector<string> words = Parser::NormalizeText(query);
    return _rank.CuttingList(words, _idx);
}
