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
    unsigned long len = query.size();                               // количество слов в запросе
    if(len >0)
    {
        Statistics* stat = idx->GetStat();                              // статистика
        double AVGlen = stat->GetAverageLen();                          // средняя длина док-та
        unsigned long N = stat->GetCountTxt();                          // кол-во документов
        vector < pair < double, unsigned long > > rank(N);

        for(unsigned long i = 0; i < len; i++)
        {
            if(!stat->IsStopWord ( query[i]))                               // если стоп-слово -- пропустить
            {
                PostingList* pl = idx->FindPos(query[i]);                   // загрузить постинг лист для слова из запроса
                if(pl)
                {
                    unsigned long df = pl->Length();                        // получить количество вх. слова из запроса в док-ты
                    for(unsigned long docId = 1; docId <= N; docId++)
                    {
                        if(stat->GetTxtLen(docId))
                        {

                            unsigned long lenD = stat->GetTxtLen(docId);        // длина текущего документа
                            unsigned long tf = pl->LengthEnt(docId);            //получить кол-во вхождений в текущий документ
                            double W = bm25_weight(tf, df, N, lenD, AVGlen);	// вычислить вес слова
                            if(i == 0)
                            {
                                pair<double, unsigned long> tempPair(W, docId);
                                rank[docId] = tempPair;
                            }
                            else
                            {
                                rank[docId].first += W;                         // добавить вес в нужный вектор
                            }
                            delete pl;
                        }
                    }
                }
            }
        }

        PostingList* result = new PostingList();
        if(rank.empty())                                               // если все найденное - стоп-слова или ни одно из слов вообще не найдено
        {
            for(unsigned long i = 1; i <= 200; i++)
                    result->Add(i, 0);                                 // забить первыми документами из базы
            return result;
        }

        sort(rank.begin(), rank.end());                                 // сортируем полученные результаты по весу

        for(unsigned long i = _maxRank-1, k= 0; k < 200 && k < rank.size(); k++,i--)
           result->Add(rank[i].second, 0);

        if(result->Length() < 200)
        {
            for(unsigned  i = 200-result->Length()+1; i <= 200; i++)
            {
                result->Add(i, 0);
            }
        }
        return result;
    }
    else
    {
            PostingList* result = new PostingList();
            for(unsigned long i = 1; i <= 200; i++)
                    result->Add(i, 0);                                 // забить первыми документами из базы
            return result;
    }


}
