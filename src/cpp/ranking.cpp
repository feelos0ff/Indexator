/*
* ranking.cpp
*
* Created on: 02 июня 2014 г.
* Author: feelosoff
*/

#include "../headers/ranking.h"


double Ranking::idf(unsigned long df, unsigned long N)
{
    if(df == 0)
        return 0;
    return log10((double)N/df);
}
/*
double weight(unsigned long tf, unsigned long N, unsigned long df)
{
if(tf == 0)
return 0;
return (1 + log10(tf)) * idf(df, N);
}
*/
double Ranking::bm25_weight(unsigned long tf, unsigned long df, unsigned long N, int lenD, int avgDl)
{
    double k = 2.0, b = 0.75;
    return idf(df, N) * (tf * (k + 1) / (tf + k * (1 - b + b * (lenD) / avgDl ) ) );
}


PostingList* Ranking::CuttingList(vector<string> &query, IndexTable *idx)
{
    unsigned long len = query.size(); // количество слов в запросе
    Statistics* stat = idx->GetStat(); // статистика
    double AVGlen = stat->GetAverageLen(); // средняя длина док-та
    unsigned long N = stat->GetCountTxt(); // кол-во документов
    vector < pair < double, unsigned long > > rank(N);

    for(unsigned long i = 0; i < len; i++)
    {
        PostingList* pl = idx->FindPos(query[i]); // загрузить постинг лист для слова из запроса
        if(pl)
        {
            unsigned long df = pl->Length(); // получить количество вх. слова из запроса в док-ты
            for(unsigned long docId = 0; docId < N; docId++)
            {
                unsigned long lenD = stat->GetTxtLen(docId); // длина текущего документа
                unsigned long tf = pl->LengthEnt(docId); //получить кол-во вхождений в текущий документ
                double W = bm25_weight(tf, df, N, lenD, AVGlen);	// вычислить вес слова
                if(i == 0)
                {
                    pair<double, unsigned long> tempPair(W, docId);
                    rank[docId] = tempPair;
                }
                else
                {
                    rank[docId].first += W; // добавить вес в нужный вектор
                }
                delete pl;
            }
        }
    }

    if(rank.empty())
    {
        cout << "По вашему запросу ничего не найдено. Попробуйте переформулироватьзапрос\n";
        return NULL;
    }
    sort(rank.begin(), rank.end());

    PostingList* result = new PostingList();
    for(unsigned long i = _maxRank-1, k= 0; k < 200; k++,i--)
       result->Add(rank[i].second, 0);

   return result;
}
