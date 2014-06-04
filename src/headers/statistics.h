/*
 * statistics.h
 *
 *  Created on: 02 июня 2014 г.
 *      Author: feelosoff
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_


class Statistics{

public:

	double GetAverageLen();						///< средняя длина документа в словах
	unsigned long GetCountTxt();				///< количество текстов
	unsigned long GetTxtLen(unsigned long);		///< длина данного текста
};


#endif /* STATISTICS_H_ */
