/*
 * dbworker.h
 *
 *  Created on: 02 июня 2014 г.
 *      Author: feelosoff
 */

#ifndef DBWORKER_H_
#define DBWORKER_H_
#include "definesincludes.h"


class DBWorker{

public:
	string GetNewsText(int);
    string GetPrepText(int);
    string GetMetaData(int);
    unsigned long GetCountTxt();				///< количество текстов

    void SetPrepText(vector<string>&);
};



#endif /* DBWORKER_H_ */
