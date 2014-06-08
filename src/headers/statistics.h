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
	typedef map <string,pair< unsigned long,unsigned long> >::iterator WordIter;
	///< отображение номер слова на вхождение
	vector< WordIter > _wordAccess;

	///< слово, номер слова, количество вхождений слова
	map <string,pair< unsigned long,unsigned long> > _wordDict;

	///< массив длин документов
	vector <unsigned long> _txtDict;

	double _stopLine;		///< порог стоп-слова

	unsigned long _wc;		///< суммарный счётчик слов

	unsigned long long _numsInArc;		///< количество несжатых данных
	unsigned long long _byteInArc;		///< количество данных после сжатия

public:

	Statistics(double stopLine = 0.85): _stopLine(stopLine), _wc(0), _numsInArc(0), _byteInArc(0){}

	void SetStopLine(double);

	void AddArc(unsigned long long, unsigned long long);	///< добавление для подсчёта статистики по сжатию

	long double GetArcStat();

	void Dump(string);
	void Load(string);

	void AddWord(string, unsigned long);				///< добавление слово-номер документа

	pair<string, unsigned long> GetWord(unsigned long);		///< по заданному номеру слова получить слово и кол-во вхождений

	unsigned long GetWord(string);				///< по заданному слову получить номер слова
	unsigned long WordCount();					///< количество слов

	bool IsStopWord(string);					///< проверка на то, является ли стоп-словом
	bool IsStopWord(unsigned long);				///< проверка на то, является ли стоп-словом на вход номер слова

	double GetAverageLen();						///< средняя длина документа в словах

	unsigned long GetCountTxt();				///< количество текстов
	unsigned long GetTxtLen(unsigned long);		///< длина данного текста

	void Commit();								///< заполняет номера слов
};


#endif /* STATISTICS_H_ */
