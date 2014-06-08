/*
 * dbworker.h
 *
 *  Created on: 02 июня 2014 г.
 *      Author: feelosoff
 */

#ifndef DBWORKER_H_
#define DBWORKER_H_
#include "definesincludes.h"
#include "parser.h"

class DBWorker{

	PGconn *_conn;

	string Select(string, unsigned int);

public:

	DBWorker();
	~DBWorker();

	string GetNewsText(unsigned int);
    string GetPrepText(unsigned int);
    string GetMetaData(unsigned int);

    unsigned long GetMaxId();

    unsigned long GetCountTxt();				///< количество текстов

    void SetPrepText(vector<string>&, unsigned int);
};



#endif /* DBWORKER_H_ */
