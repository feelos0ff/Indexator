/*
 * statistics.h
 *
 *  Created on: 02 июня 2014 г.
 *      Author: feelosoff
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_
#include "definesincludes.h"
#include "parser.h"
#include "filework.h"

class Statistics{

	map <string, unsigned long> _wordDict;
	///< toDo переделать на вектор документов
	map <unsigned long, unsigned long> _txtDict;

	double _stopLine;

	unsigned long _wc;

public:

	Statistics(double stopLine = 0.85): _stopLine(stopLine), _wc(0){}

	void SetStopLine(double);

	void Dump(string);
	void Load(string);

	void AddWord(string, unsigned long);

	unsigned long WordCount();					///< количество слов

	bool IsStopWord(string);					///< проверка на то, является ли стоп-словом
	double GetAverageLen();						///< средняя длина документа в словах

	unsigned long GetCountTxt();				///< количество текстов
	unsigned long GetTxtLen(unsigned long);		///< длина данного текста
};


#endif /* STATISTICS_H_ */
